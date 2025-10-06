#pragma once

#include <filesystem>

#include "Animate/XFL/File.h"
#include "Animate/XFL/Writer.h"

#include "core/math/color_rgba.h"
#include "core/math/color_rgb.h"
#include "core/math/rect.h"
#include "core/memory/ref.h"
#include "core/generic/non_copyable.h"
#include "core/parallel/bs_thread_pool.hpp"

#include "Animate/Document/LibraryController.h"
#include "Animate/Library/LibraryItem/LibraryFolder.h"
#include "Animate/Library/LibraryItem/MediaElem.h"
#include "Animate/Library/LibraryItem/Media/MediaBits.h"
#include "Animate/Library/LibraryItem/DocumentPage.h"
#include "Vector/LibraryItemVector.h"

namespace Animate::Document
{
	using wk::Ref;
	using wk::Unique;


	/// <summary>
	/// Document root class
	/// </summary>
	class SketchDocument
	{	
	private:
		friend LibraryController;
		NON_COPYABLE(SketchDocument);

	public:
		static inline size_t s_SaveThreadsCount = std::thread::hardware_concurrency();

	private:
		static BS::thread_pool<0>& GetSavePool() {
			static BS::thread_pool<0> pool(SketchDocument::s_SaveThreadsCount);
			return pool;
		}

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
		void WriteXFL(const Path& path) const;
		void WriteXFLFolders(XFL::XFLFile& file, XFL::XFLWriter& writer) const;
		void WriteXFLMedia(XFL::XFLFile& file, XFL::XFLWriter& writer) const;
		void WriteXFLSymbols(XFL::XFLFile& file, XFL::XFLWriter& writer) const;

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

		template<typename T, typename... Args>
		T& CreateSymbol (Args&&... args)
		{
			return symbols.Add<T>(std::forward<Args>(args)...);
		}

		template<typename T, typename... Args>
		T& CreateScene(Args&&... args)
		{
			return scenes.Add<T>(std::forward<Args>(args)...);
		}

	private:
		int m_frameRate = 24;
		wk::ColorRGB m_backgroundColor = {0xFF, 0xFF, 0XFF};
		wk::Rect m_bounds{0, 0, 550, 450};
		LibraryController m_controller;

	private:
		LibraryItemsVector<Library::LibraryFolder> libraryFolders;
		LibraryItemsVector<Library::MediaElem> mediaElements;
		LibraryItemsVector<Library::DocumentPage> symbols;
		LibraryItemsVector<Library::DocumentPage> scenes;
	};
}