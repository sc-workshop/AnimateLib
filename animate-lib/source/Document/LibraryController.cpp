#include "LibraryController.h"
#include "Document/SketchDocument.h"

namespace Animate::Document
{
	LibraryController::LibraryController(SketchDocument& document) : m_document(document)
	{
	}

	void LibraryController::ReserveFolders(size_t capacity)
	{
		m_document.libraryFolders.Reserve(capacity);
	}

	Library::LibraryFolder& LibraryController::MakeFolder(const std::u16string& name, const Library::LibraryItemID& id)
	{
		auto folder = m_document.libraryFolders.Find(
			[&name, &id](const auto& item)
			{
				if (item->GetParentID() == id && item->GetLibraryName() == name)
				{
					return true;
				}

				return false;
			}
		);

		if (folder) return *folder;

		auto& result = m_document.CreateFolder<Library::LibraryFolder>(m_document, name);
		Library::LibraryItemID folder_id;
		folder_id.GenerateUniqueID();
		result.SetID(folder_id);

		return result;
	}

	Library::LibraryFolder& LibraryController::MakeFolders(const std::filesystem::path& path)
	{
		Library::LibraryFolder* current_folder = nullptr;
		Library::LibraryItemID last_folder_id = Library::LibraryItemID::NoParent;

		std::u16string folder_path = path.u16string();
		size_t position = 0;
		bool valid = true;
		while (valid)
		{
			size_t new_position = folder_path.find(u"/", position);
			if (new_position == std::string::npos)
			{
				valid = false;
				new_position = folder_path.length();
			};

			std::u16string current_name = folder_path.substr(position, new_position - position);
			current_folder = &MakeFolder(current_name, last_folder_id);
			if (last_folder_id != Library::LibraryItemID::NoParent)
			{
				current_folder->SetParentID(last_folder_id);
			}

			last_folder_id = current_folder->GetID();
			position = new_position + 1;
		}

		return *current_folder;
	}

	Library::LibraryFolder* LibraryController::GetFolder(const Library::LibraryItemID& id)
	{
		return m_document.libraryFolders.Get(id);
	}

	LibraryReferenceVector LibraryController::GetFolderItems(const Library::LibraryItemID& id)
	{
		LibraryReferenceVector result;

		auto processer = [&result, &id](auto& input)
			{
				for (size_t i = 0; input.Length() > i; i++)
				{
					auto& item = input.At(i);
					if (item.GetParentID() == id)
					{
						result.AddInplace(&item);
					}
				}
			};

		processer(m_document.libraryFolders);
		processer(m_document.mediaElements);

		return result;
	}

	Library::MediaBits& LibraryController::MakeBitmap(const std::filesystem::path& path)
	{
		std::u16string name;
		Library::LibraryItemID parent;
		GetItemValidNameAndParent(path.u16string(), name, parent, u"Bitmap");

		Library::MediaBits& result = m_document.CreateMedia<Library::MediaBits>(m_document, name);
		result.Create();

		Library::LibraryItemID folder_id;
		folder_id.GenerateUniqueID();
		result.SetID(folder_id);
		result.SetParentID(parent);

		return result;
	}

	void LibraryController::GetItemValidNameAndParent(const std::u16string& item_name, std::u16string& name, Library::LibraryItemID& parent, const std::u16string& basename)
	{
		if (item_name.find(u"/") != std::u16string::npos)
		{
			fs::path path(item_name);
			fs::path parent_path = path.parent_path();
			parent = MakeFolders(parent_path).GetID();
			name = path.filename().u16string();
		}
		else
		{
			name = item_name;
			parent = Library::LibraryItemID::NoParent;
		}

		LibraryReferenceVector folder = GetFolderItems(parent);
		if (name.empty())
		{
			name = GenerateUniqueName(basename, folder);
		}
		else
		{
			if (folder.Contains(name))
			{
				name = GenerateUniqueName(name, folder);
			}
		}
	}

	std::u16string LibraryController::GenerateUniqueName(const std::u16string& basename, LibraryReferenceVector& folder) const
	{
		size_t counter = 1;
		std::u16string current_name = basename;
		auto update_name = [&current_name, &counter, &basename]()
			{
				current_name = basename + u" " + wk::StringConverter::ToUTF16(std::to_string(counter++));
			};

		while (folder.Contains(current_name))
		{
			update_name();
		}

		return current_name;
	}
}