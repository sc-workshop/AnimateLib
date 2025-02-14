#pragma once

#include "Library/LibraryItem/MediaElem.h"
#include "Assets/Bitmap.h"
#include "XFL/DOM/Items/DOMBitmapItem.h"

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

		void FromImage(const std::filesystem::path& path);
		void UpdateImage(const std::filesystem::path& path);

		virtual void WriteXFL(XFL::XFLFile& file, XFL::XFLWriter& writer) const override;
		virtual void WriteXFLContent(XFL::XflIoFile& file) const;

		void InitializeDOMItem(DOM::DOMBitmapItem& item) const;

	private:
		time_t m_last_update = 0;
		bool m_allow_smooth = false;
		CompressionType m_compression = CompressionType::Lossless;
		int m_quality = 0;

		Bitmap m_bitmap;
	};
}