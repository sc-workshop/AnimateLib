#include "LibraryFolder.h"

#include "Document/SketchDocument.h"
#include "XFL/DOM/DOMItem.h"

namespace Animate::Library
{
	LibraryFolder::LibraryFolder(Document::SketchDocument& document, std::optional<std::u16string> name) : LibraryItem(document)
	{
		if (name.has_value())
		{
			m_item_name = name.value();
		}
	}

	void LibraryFolder::WriteXFL(XFL::XFLWriter& writer) const
	{
		DOM::DOMItem item(DOM::DOMItem::Type::Folder);
		item.name = XFL::XFLWriter::MakePrefferedPath(GetLibraryItemPath());

		writer.WriteDOMFolderItem(item, IsExpanded());
	}
}