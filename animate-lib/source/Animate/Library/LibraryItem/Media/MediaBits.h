#pragma once

#include "Animate/XFL/File.h"
#include "Animate/Library/LibraryItem/MediaElem.h"
#include "Animate/Assets/Bitmap.h"
#include "Animate/XFL/DOM/Items/DOMBitmapItem.h"

namespace Animate::Library
{
	/// <summary>
	/// Bitmap symbol
	/// </summary>
	class MediaBits : public MediaElem
	{
	public:
		enum class CompressionType
		{
			Unknown = 0,
			Photo,
			Lossless
		};
	public:
		using MediaElem::MediaElem;

	public:
		virtual bool IsMediaBits() const override
		{
			return true;
		}

		virtual bool Loaded() const override
		{
			return m_bitmap.Loaded();
		}

	public:
		bool GetAllowSmooth() const { return m_allow_smooth; }
		void SetAllowSmooth(bool status) { m_allow_smooth = status; }

		CompressionType GetCompression() const { return m_compression; }
		void SetCompression(CompressionType status) { m_compression = status; }

		int GetQuality() const { return m_quality; }
		void SetQuality(int status) { m_quality = status; }

		
		void UpdateImage(const Path& path);
		void CreateBits(const Path& path);
		void CreateBits(const wk::RawImage& image);

		virtual void WriteXFL(XFL::XFLFile& file, XFL::XFLWriter& writer) const override;
		virtual void WriteXFLContent(XFL::XflIoFile& file) const override;

		void InitializeDOMItem(DOM::DOMBitmapItem& item) const;

		const Bitmap& GetBitmap() const { return m_bitmap; }

	private:
		time_t m_last_update = 0;
		bool m_allow_smooth = false;
		CompressionType m_compression = CompressionType::Lossless;
		int m_quality = 50;

		Bitmap m_bitmap;
	};
}