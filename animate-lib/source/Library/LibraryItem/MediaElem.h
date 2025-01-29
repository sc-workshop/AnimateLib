#pragma once

#include "Library/LibraryItem.h"
#include "XFL/IoFile.h"

#include <filesystem>

namespace Animate::Library
{
	class MediaElem : public LibraryItem
	{
	private:
		static inline size_t MediaCounter = 0;

	public:
		MediaElem(Document::SketchDocument& document, const std::u16string& name = u"");

	public:
		virtual bool IsMedia() const override
		{
			return true;
		}

		virtual bool IsMediaBits() const
		{
			return false;
		}

		virtual bool IsMediaVideoStream() const
		{
			return false;
		}

		virtual bool IsMediaSwfPage() const
		{
			return false;
		}

		virtual bool IsLibraryMediaElem() const
		{
			return true;
		}

		virtual bool Loaded() const
		{
			return false;
		}

	public:
		virtual void Create();

		virtual void WriteXFL(XFL::XFLWriter& /*writer*/) const override
		{
		};

		virtual void WriteXFLContent(XFL::XflIoFile& /*file*/) const
		{
		};

		virtual std::string GetXFLMediaName() const { return m_media_filename; }
		virtual std::filesystem::path GetXFLMediaPath() const { return GetXFLMediaName(); }

	protected:
		void UpdateFromSource();
		void InitializeDOMItem(DOM::DOMMediaItem& item) const;

	protected:
		time_t m_last_source_update = 0;
		std::filesystem::path m_source_path;
		std::string m_media_filename;
	};
}