#include "Bitmap.h"

#include <algorithm>

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
        bool should_compress = 0x6400000 > image.data_length();
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

    void Bitmap::FromImage(const Path& path)
	{
        wk::InputFileStream file(path);

        wk::RawImageRef image;
        wk::stb::load_image(file, image);
		FromImage(*image);
	}

    void Bitmap::FromImage(const wk::RawImage& image)
    {
		FromData(image.width(), image.height());
        image.copy(*m_image);
        CleanUpAlpha();
        FixPixelOrder();
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

    void Bitmap::GuessAlpha(int& alpha_type, wk::ColorRGBA& color_factor, bool strict_alpha) const
    {
        alpha_type = 0;

        if ((uint32_t)m_depth >= 3)
        {
            bool hasAlpha = false;
            bool isOpaque = true;
            bool is_colorfill = true;

            if (m_depth == Depth::RGBA)
            {
				uint16_t width = m_image->width();
				uint16_t height = m_image->height();

                for (uint16_t h = 0; h < height; ++h)
                {
                    for (uint16_t w = 0; w < width; ++w)
                    {
                        const wk::ColorRGBA& pixel = m_image->at<wk::ColorRGBA>(w, h);

                        if (pixel.a != 0xFF)
                        {
                            hasAlpha = true;
                            if (pixel.a == 0)
                            {
                                color_factor = pixel;
                                is_colorfill = false;
                            }

                            if (color_factor.r > color_factor.a || color_factor.g > color_factor.a || color_factor.b > color_factor.a)
                                isOpaque = false;
                        }
                    }
                }
            }
            else
            {

            }


            if (hasAlpha)
            {
				bool validColorFactor = color_factor.r | color_factor.g | color_factor.b;

                if (!is_colorfill && !strict_alpha)
                {
                    if (validColorFactor || !isOpaque)
                        alpha_type = 1;
                    else
                        alpha_type = 2;
                }
            }
        }
    }

    void Bitmap::AdjustAlpha(int alpha_type, wk::ColorRGBA color_factor, int32_t a4)
    {
        if (!alpha_type)
            return;

        if (alpha_type == 2) {
            if (m_depth == Depth::RGBA) {
                if (a4 <= 0) {
                    for (uint16_t h = 0; h < m_image->height(); ++h)
                    {
                        for (uint16_t w = 0; w < m_image->width(); ++w)
                        {
                            wk::ColorRGBA& pixel = m_image->at<wk::ColorRGBA>(w, h);
                            if (pixel.a == 255) continue;

                            if (pixel.a) {
                                uint8_t invAlpha = 255 - pixel.a;

                                uint8_t r = pixel.r - (invAlpha * color_factor.r);
                                uint8_t g = pixel.g - (invAlpha * color_factor.g);
                                uint8_t b = pixel.b - (invAlpha * color_factor.b);

                                pixel.r = std::clamp<uint8_t>(r, 0, pixel.a);
                                pixel.g = std::clamp<uint8_t>(g, 0, pixel.a);
                                pixel.b = std::clamp<uint8_t>(b, 0, pixel.a);
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

            // TODO: depth 5?
        }
		else if (alpha_type == 1)
        {
            if ((color_factor.r | color_factor.g | color_factor.b) == 0)
                return;

            if (m_depth == Depth::RGBA) {
                if (a4 <= 0) {
                    for (uint16_t h = 0; h < m_image->height(); ++h)
                    {
                        for (uint16_t w = 0; w < m_image->width(); ++w)
                        {
                            wk::ColorRGBA& pixel = m_image->at<wk::ColorRGBA>(w, h);
                            if (pixel.a == 255) continue;

                            if (pixel.a) {
                                int r = pixel.a * pixel.r;
                                int g = pixel.a * pixel.g;
                                int b = pixel.a * pixel.g;

                                pixel.r = (uint8_t)std::min(r, pixel.a + 1);
                                pixel.g = (uint8_t)std::min(g, pixel.a + 1);
                                pixel.b = (uint8_t)std::min(b, pixel.a + 1);
                            }
                            else {
                                pixel.r = 0;
                                pixel.g = 0;
                                pixel.b = 0;
                            }
                        }
                    }
                }
            }
        }

        // TODO: alpha type 1
    }

    void Bitmap::FixPixelOrder()
    {
        if (m_depth == Depth::RGBA)
        {
            wk::ColorRGBA buffer;
            for (uint16_t h = 0; m_image->height() > h; h++)
            {
                for (uint16_t w = 0; m_image->width() > w; w++)
                {
                    wk::ColorRGBA& pixel = m_image->at<wk::ColorRGBA>(w, h);

                    if (pixel.a)
                    {
                        buffer = pixel;

                        pixel.r = buffer.a;
                        pixel.g = buffer.r;
                        pixel.b = buffer.g;
                        pixel.a = buffer.b;
                    }
                }
            }
        }
    }
}