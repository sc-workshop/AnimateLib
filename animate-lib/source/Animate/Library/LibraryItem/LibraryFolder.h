#pragma once

#include <optional>
#include <filesystem>

#include "Animate/Library/LibraryItem.h"
#include "Animate/XFL/DOM/Items/DOMFolderItem.h"

namespace Animate::Library
{
	/// <summary>
	/// List of other library items
	/// </summary>
	class LibraryFolder : public LibraryItem
	{
	public:
		using LibraryItem::LibraryItem;

	public:
		virtual bool IsFolder() const override
		{
			return true;
		}

		virtual bool IsExpanded() const { return m_expanded; }
		virtual void SetExpanded(bool status) { m_expanded = status; }

#pragma region Object capabilities
		virtual bool CanBeParent() const override
		{
			return true;
		}
#pragma endregion

	public:
		virtual void WriteXFL(XFL::XFLFile& file, XFL::XFLWriter& writer) const override;
		void InitializeDOMItem(DOM::DOMFolderItem& item) const;

	private:
		Path m_library_path;
		bool m_expanded = false;
	};
}