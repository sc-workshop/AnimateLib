#pragma once

#include <string>

#include "Document/Vector/LibraryItemVector.h"
#include "Library/LibraryItem/LibraryFolder.h"
#include "Library/LibraryItem/Media/MediaBits.h"
#include "Library/LibraryItem/DocumentPage.h"

namespace Animate::Document
{
	class SketchDocument;

	/// <summary>
	/// Separate class to control over Root library
	/// </summary>
	class LibraryController
	{
	public:
		LibraryController(SketchDocument& document);
			
	public:
		Library::LibraryFolder& MakeFolder(const std::u16string& name, const Library::LibraryItemID& folder_id = Library::LibraryItemID::NoParent);
		Library::LibraryFolder& MakeFolders(const Path& path);

		Library::LibraryFolder* GetFolder(const Library::LibraryItemID& id);
		LibraryReferenceVector GetFolderItems(const Library::LibraryItemID& folder_id);

		Library::MediaBits& MakeBitmap(const Path& path);
		Library::DocumentPage& MakeSymbol(const Path& path, Library::DocumentPage::SymbolType type);

		void GetItemValidNameAndParent(const std::u16string& path, std::u16string& name, Library::LibraryItemID& parent, const std::u16string& basename = u"Item");

	private:
		std::u16string GenerateUniqueName(const std::u16string& basename, LibraryReferenceVector& folder) const;

	private:
		SketchDocument& m_document;
	};
}