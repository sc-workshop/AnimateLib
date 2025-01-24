#pragma once

#include <filesystem>

#include "XFL/File.h"
#include "XFL/Writer.h"

#include "core/math/color_rgba.h"
#include "core/math/color_rgb.h"
#include "core/math/rect.h"
#include "core/memory/ref.h"
#include "core/generic/non_copyable.h"

#include "Document/LibraryController.h"
#include "Library/LibraryItem/LibraryFolder.h"
#include "Library/LibraryItem/MediaElem.h"
#include "Library/LibraryItem/Media/MediaBits.h"
#include "Vector/LibraryItemVector.h"

namespace Animate::Document
{
	using wk::Ref;
	using wk::Unique;

	class SketchDocument
	{	
	private:
		friend LibraryController;
		NON_COPYABLE(SketchDocument);

	public:
		SketchDocument();
		virtual ~SketchDocument() = default;

	public:
		int GetFrameRate() const { return m_frameRate; };
		void SetFrameRate(const int rate) { m_frameRate = rate; };

		const wk::ColorRGB& GetBackgoundColor() const { return m_backgroundColor; };
		void SetBackgroundColor(const wk::ColorRGB color) { m_backgroundColor = color; };

		const wk::Rect& GetPaperBounds() const { return m_bounds; };
		void SetPaperBounds(const wk::Rect bound) { m_bounds = bound; };

	public:
		XFL::XFLWriter CreateXFLDOMWriter() const;
		void WriteXFL(const std::filesystem::path& path) const;
		void WriteXFLFolders(XFL::XFLWriter& writer) const;
		void WriteXFLMedia(XFL::XFLWriter& writer) const;

	public:
		LibraryController& GetController() { return m_controller;  }

	private:
		template<typename T, typename ... Args>
		T& CreateFolder(Args&& ... args)
		{
			return libraryFolders.Add<T>(std::forward<Args>(args)...);
		}

		template<typename T, typename... Args>
		T& CreateMedia(Args&&... args)
		{
			return mediaElements.Add<T>(std::forward<Args>(args)...);
		}

	private:
		int m_frameRate = 24;
		wk::ColorRGB m_backgroundColor = {0xFF, 0xFF, 0XFF};
		wk::Rect m_bounds{0, 0, 1024, 1024};
		LibraryController m_controller;

	private:
		LibraryItemsVector<Library::LibraryFolder> libraryFolders;
		LibraryItemsVector<Library::MediaElem> mediaElements;
	};
}