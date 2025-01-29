#include "Bitmap.h"

namespace Animate
{
    Bitmap Bitmap::m_sDefaultFallback = Bitmap();

    void Bitmap::WriteXFLContent(XFL::XflIoFile& file) const
    {
        wk::RawImage& image = GetImage();

        file.write_unsigned_byte((uint8_t)GetMediaType());  // Media Type
        file.write_unsigned_byte(5);                        // Depth, RGBA only for now
        uint16_t row_size = (uint16_t)wk::Image::calculate_image_length(image.width(), 1, image.depth());
        file.write_unsigned_short(row_size);                // Bytes per row
        file.write_unsigned_short(image.width());           // Width
        file.write_unsigned_short(image.height());          // Height

        auto bounds = GetBounds();
        file.write_int(bounds.x);
        file.write_int(bounds.width);
        file.write_int(bounds.y);
        file.write_int(bounds.height);

        bool has_alpha = image.base_type() == wk::Image::BasePixelType::RGBA;
        bool should_compress = false;//0x6400000 > image.data_length();
        file.write_bool(has_alpha);
        file.write_bool(should_compress);

        if (should_compress)
        {
            file.CompressChunked(image.data(), image.data_length(), 4096 * 4);
        }
        else
        {
            file.write(image.data(), image.data_length());
        }
    }

    wk::Rect Bitmap::GetBounds() const
    {
        wk::RawImage& image = GetImage();

        wk::Rect result;
        result.width = image.width() * 20;
        result.height = image.height() * 20;

        return result;
    }

    uint8_t* Bitmap::FromData(uint16_t width, uint16_t height)
    {
        m_image = wk::CreateRef<wk::RawImage>(width, height, wk::Image::PixelDepth::RGBA8);
        m_depth = Depth::RGBA;
        return m_image->data();
    }

    void Bitmap::FromImage(const std::filesystem::path& path)
	{
        wk::InputFileStream file(path);

        wk::RawImageRef image;
        wk::stb::load_image(file, image);
        FromData(image->width(), image->height());
        image->copy(*m_image);

        CleanUpAlpha();

        // RGBA -> ARGB
        //for (uint16_t h = 0; m_image->height() > h; h++)
        //{
        //    for (uint16_t w = 0; m_image->width() > w; w++)
        //    {
        //        wk::ColorRGBA& pixel = m_image->at<wk::ColorRGBA>(w, h);
        //        wk::ColorRGBA buffer = pixel;
        //        
        //        pixel.r = buffer.a;
        //        pixel.g = buffer.r;
        //        pixel.b = buffer.g;
        //        pixel.a = buffer.b;
        //    }
        //}
	}

    void Bitmap::CleanUpAlpha()
    {
        if (m_depth != Depth::RGBA) return;

        int alpha_type;
        wk::ColorRGBA factor;
        GuessAlpha(alpha_type, factor);
        AdjustAlpha(alpha_type, factor);
    }

    Bitmap& Bitmap::GetDefaultFallback()
    {
        if (!m_sDefaultFallback.Loaded())
        {
            m_sDefaultFallback.FromData(32, 32);
        }

        return m_sDefaultFallback;
    }

    wk::RawImage& Bitmap::GetImage() const
    {
        if (!Loaded())
        {
            return GetDefaultFallback().GetImage();
        }

        return *m_image;
    }

    void Bitmap::GuessAlpha(int& alpha_type, wk::ColorRGBA& unk_factor) const
    {
        alpha_type = 0;

        bool has_alpha = true;
        bool is_empty_image = true;
        bool is_premultiplied = true;

        if (0 >= m_image->width() || 0 >= m_image->height())
        {
            has_alpha = false;
            is_empty_image = true;
        }
        else
        {
            for (uint16_t h = 0; m_image->height() > h; h++)
            {
                for (uint16_t w = 0; m_image->width() > w; w++)
                {
                    const wk::ColorRGBA& pixel = m_image->at<wk::ColorRGBA>(w, h);

                    if (pixel.a)
                    {
                        if (pixel.a != 0xFF) has_alpha = true;
                        is_empty_image = false;
                    }
                    else
                    {
                        unk_factor = pixel;
                        unk_factor.a = 0xFF;
                        has_alpha = true;
                    }

                    if (pixel.r > pixel.a || pixel.g > pixel.a || pixel.b > pixel.a)
                    {
                        is_premultiplied = false;
                    }
                }
            }
        }

        if (has_alpha && !is_empty_image)
        {
            if (unk_factor.r && unk_factor.g && unk_factor.b && is_premultiplied)
            {
                alpha_type = 2;
            }
            else
            {
                alpha_type = 1;
            }
        }
    }

    // thats a fucking magic
    // its looks ugly but it just works
    void Bitmap::AdjustAlpha(int alpha_type, wk::ColorRGBA unk_factor)
    {
        if (alpha_type == 0 || alpha_type == 2) return;

        for (uint16_t h = 0; m_image->height() > h; h++)
        {
            for (uint16_t w = 0; m_image->width() > w; w++)
            {
                wk::ColorRGBA& pixel = m_image->at<wk::ColorRGBA>(w, h);

                if (pixel.a != 0xFF && pixel.a)
                {
                    int alpha_inv = pixel.a ^ 0xFF;
                    int r = pixel.r - ((unk_factor.r * (alpha_inv) >> 8));
                    int g = pixel.g - ((unk_factor.g * (alpha_inv) >> 8));
                    int b = pixel.b - ((unk_factor.b * (alpha_inv) >> 8));

                    if (r < 0) r = 0;
                    if (r > pixel.a)
                    {
                        r = pixel.a;
                    }

                    if (g < 0) g = 0;
                    if (g > pixel.a)
                    {
                        g = pixel.a;
                    }

                    if (b < 0) b = 0;
                    if (b > pixel.a)
                    {
                        b = pixel.a;
                    }

                    pixel.r = r;
                    pixel.g = g;
                    pixel.b = b;
                }
            }
        }

        if ((uint8_t)m_depth > 3)
        {
            for (uint16_t h = 0; m_image->height() > h; h++)
            {
                for (uint16_t w = 0; m_image->width() > w; w++)
                {
                    wk::ColorRGBA& pixel = m_image->at<wk::ColorRGBA>(w, h);

                    if (pixel.a != 0xFF && pixel.a)
                    {
                        int alpha_inv = pixel.a ^ 0xFF;
                        int r = pixel.r;
                        int g = pixel.g;
                        int b = pixel.b;
                        int a = pixel.a + 1;

                        b = (a * b) >> 8;
                        g = (a * g) >> 8;
                        r = (a * r) >> 8;

                        if (r < 0) r = 0;
                        if (r > a)
                        {
                            r = a;
                        }

                        if (g < 0) g = 0;
                        if (g > a)
                        {
                            g = a;
                        }

                        if (b < 0) b = 0;
                        if (b > a)
                        {
                            b = a;
                        }

                        pixel.r = r;
                        pixel.g = g;
                        pixel.b = b;
                    }
                }
            }
        }

        for (uint16_t h = 0; m_image->height() > h; h++)
        {
            for (uint16_t w = 0; m_image->width() > w; w++)
            {
                wk::ColorRGBA& pixel = m_image->at<wk::ColorRGBA>(w, h);

                if (pixel.a)
                {
                    wk::ColorRGBA& pixel = m_image->at<wk::ColorRGBA>(w, h);
                    wk::ColorRGBA buffer = pixel;

                    pixel.r = buffer.a;
                    pixel.g = buffer.r;
                    pixel.b = buffer.g;
                    pixel.a = buffer.b;
                }
                else
                {
                    pixel.r = 0;
                    pixel.g = 0;
                    pixel.b = 0;
                }
            }
        }
    }
}