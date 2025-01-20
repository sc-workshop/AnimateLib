#pragma once

#include <string>

#include "Library/LibraryItem/LibraryFolder.h"

namespace Animate::Document
{
	class SketchDocument;

	class LibraryController
	{
	public:
		LibraryController(SketchDocument& document);

	public:
		void ReserveFolders(size_t capacity);
		Library::LibraryFolder& MakeFolder(const std::u16string& name);

		Library::LibraryFolder* GetFolder(const Library::LibraryItemID& id);

	private:
		SketchDocument& m_document;
	};
}