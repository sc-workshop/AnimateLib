#include "LibraryItem.h"
#include "Document/SketchDocument.h"

namespace Animate::Library
{
	LibraryItem::LibraryItem(Document::SketchDocument& document) : m_document(document)
	{ }

	bool LibraryItem::SetParent(const LibraryItem& parent)
	{
		if (!parent.CanBeParent()) return false;

		SetParentID(parent.GetID());
		return true;
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
		};

		LibraryFolder* folder = m_document.GetController().GetFolder(m_parent_id);
		if (folder)
		{
			m_item_path = folder->GetLibraryItemPath() / m_item_name;
		}
		else
		{
			m_item_path = m_item_name;
		}

		m_item_path_dirty = false;
	}

	void LibraryItem::SetItemPathDirty() const
	{
		m_item_path_dirty = true;
	}

	bool LibraryItem::IsItemPathDirty() const
	{
		return m_item_path_dirty;
	}

	void LibraryItem::SetLibraryItemName(const std::u16string& name) { 
		m_item_name = name;
		SetItemPathDirty();
	};

	std::u16string LibraryItem::GetLibraryItemName() const { 
		return m_item_name; 
	};

	std::filesystem::path LibraryItem::GetLibraryItemPath() const {
		if (IsItemPathDirty())
		{
			ConstructLibraryPath();
			SetItemPathDirty();
		}

		return m_item_path; 
	};
}