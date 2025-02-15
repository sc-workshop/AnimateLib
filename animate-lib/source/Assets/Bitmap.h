#pragma once

#include "core/io/file_stream.h"
#include "core/stb/stb.h"
#include "core/image/raw_image.h"

#include "MediaAsset.h"

#include <filesystem>

namespace Animate
{
	class Bitmap : public MediaAsset
	{
	private:
		static Bitmap m_sDefaultFallback;

	public:
		enum class Depth
		{
			Unknown = 0,
			IndexedRGB = 3, // Indexed RGB image with color pallete
			RGB = 4,		// Usual RGB (not sure)
			RGBA = 5		// Premultiplied RGBA
		};

	public:
		Bitmap() = default;

	public:
		virtual Type GetMediaType() const { return Type::Bitmap; };
		virtual void WriteXFLContent(XFL::XflIoFile& file) const;

	public:
		wk::Rect GetBounds() const;

		uint8_t* FromData(uint16_t width, uint16_t height);
		void FromImage(const std::filesystem::path& path);

		bool Loaded() const { return (bool)m_image; }

		void CleanUpAlpha();

	private:
		static Bitmap& GetDefaultFallback();
		wk::RawImage& GetImage() const;

		void GuessAlpha(int& alpha_type, wk::ColorRGBA& unk_factor) const;
		void AdjustAlpha(int alpha_type, wk::ColorRGBA unk_factor);

	private:
		wk::RawImageRef m_image;
		Depth m_depth = Depth::Unknown;
	};
}