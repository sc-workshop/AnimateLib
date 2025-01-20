#include "LibraryController.h"
#include "Document/SketchDocument.h"

namespace Animate::Document
{
	LibraryController::LibraryController(SketchDocument& document) : m_document(document)
	{
	}

	void LibraryController::ReserveFolders(size_t capacity)
	{
		m_document.libraryFolders.reserve(capacity);
	}

	Library::LibraryFolder& LibraryController::MakeFolder(const std::u16string& name)
	{
		auto it = std::find_if(
			m_document.libraryFolders.begin(),
			m_document.libraryFolders.end(),
			[&name](const Library::LibraryFolder& item)
			{
				if (item.HasNoParent() && item.GetLibraryItemName() == name)
				{
					return true;
				}

				return false;
			}
		);


		Library::LibraryFolder& result = it != m_document.libraryFolders.end() ?
			*it : m_document.libraryFolders.emplace_back(m_document, name);

		Library::LibraryItemID folder_id;
		folder_id.GenerateUniqueID();
		result.SetID(folder_id);

		return result;
	}

	Library::LibraryFolder* LibraryController::GetFolder(const Library::LibraryItemID& id)
	{
		auto it = std::find_if(
			m_document.libraryFolders.begin(),
			m_document.libraryFolders.end(),
			[&id](Library::LibraryFolder& folder)
			{
				return folder.GetID() == id;
			}
		);

		if (it != m_document.libraryFolders.end())
		{
			return &(*it);
		}

		return nullptr;
	}
}