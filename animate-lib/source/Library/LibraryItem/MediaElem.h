#pragma once

#include "Library/LibraryItem.h"

#include <filesystem>

namespace Animate::Library
{
	class MediaElem : public LibraryItem
	{
	private:
		static inline size_t MediaCounter = 0;

	public:
		MediaElem(Document::SketchDocument& document, const std::u16string& name);

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
		virtual time_t GetModDateForLibrary() const;
		virtual void SetModDateForLibrary(time_t);

		virtual void WriteXFL(XFL::XFLWriter& /*writer*/) const override
		{
		};

	private:
		time_t m_last_modify;
		std::filesystem::path m_source_path;
		std::string m_media_filename;
	};
}