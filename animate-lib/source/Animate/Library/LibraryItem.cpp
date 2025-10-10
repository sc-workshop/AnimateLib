#include "LibraryItem.h"

#include "Animate/Document/SketchDocument.h"
#include "Animate/XFL/DOM/Items/DOMItem.h"

namespace Animate::Library
{
	LibraryItem::LibraryItem(Document::SketchDocument& document, std::optional<std::u16string> name) : m_document(document)
	{ 
		if (name.has_value())
		{
			m_item_name = name.value();
		}
	}

	bool LibraryItem::SetParent(const LibraryItem& parent)
	{
		if (!parent.CanBeParent()) return false;

		SetParentID(parent.GetID());
		return true;
	}

	Document::SketchDocument& LibraryItem::GetSketchDoc()
	{
		return m_document;
	}

	void LibraryItem::OnParentChange()
	{
		SetItemPathDirty();
	}

	void LibraryItem::ConstructLibraryPath() const
	{
		m_item_path.clear();
		if (HasNoParent())
		{
			m_item_path = m_item_name;
		}
		else
		{
			LibraryFolder* folder = m_document.GetController().GetFolder(m_parent_id);
			if (folder)
			{
				m_item_path = folder->GetItemPath() / m_item_name;
#ifdef  _WINDOWS
				std::string path = m_item_path.string();
				std::ranges::replace(path, '\\', '/');
				m_item_path = path;
#endif //  _WINDOWS

			}
			else
			{
				m_item_path = m_item_name;
			}
		}

		m_item_path_dirty = false;
	}

	void LibraryItem::InitializeDOMItem(DOM::DOMItem& item) const
	{
		item.name = XFL::XFLWriter::MakePrefferedPath(GetItemPath());
		item.itemId = m_item_id.ToString();
	}

	void LibraryItem::SetItemPathDirty() const
	{
		m_item_path_dirty = true;
	}

	bool LibraryItem::IsItemPathDirty() const
	{
		return m_item_path_dirty;
	}

	void LibraryItem::SetItemName(const std::u16string& name) { 
		m_item_name = name;
		SetItemPathDirty();
	};

	std::u16string LibraryItem::GetItemName() const { 
		return m_item_name; 
	};

	Path LibraryItem::GetItemPath() const {
		std::lock_guard guard(m_mutex);
		if (IsItemPathDirty())
		{
			ConstructLibraryPath();
			SetItemPathDirty();
		}

		return m_item_path; 
	};

	time_t LibraryItem::GetModDateForLibrary() const
	{
		time_t result;
		std::time(&result);

		return result;
	}

	void LibraryItem::SetModDateForLibrary(time_t)
	{
	}
}