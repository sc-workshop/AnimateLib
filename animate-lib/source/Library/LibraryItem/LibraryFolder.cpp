#include "LibraryFolder.h"

#include "Document/SketchDocument.h"
#include "XFL/DOM/DOMItem.h"

namespace Animate::Library
{
	void LibraryFolder::WriteXFL(XFL::XFLWriter& writer) const
	{
		DOM::DOMItem item(DOM::DOMItem::Type::Folder);
		item.name = XFL::XFLWriter::MakePrefferedPath(GetLibraryItemPath());
		item.itemId = m_item_id.ToString();

		writer.WriteDOMFolderItem(item, IsExpanded());
	}
}