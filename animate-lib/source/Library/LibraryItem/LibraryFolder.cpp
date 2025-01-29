#include "LibraryFolder.h"

#include "Document/SketchDocument.h"
#include "XFL/DOM/Items/DOMItem.h"

namespace Animate::Library
{
	void LibraryFolder::WriteXFL(XFL::XFLWriter& writer) const
	{
		DOM::DOMItem item(DOM::DOMItem::Type::Folder);
		InitializeDOMItem(item);

		writer.WriteDOMFolderItem(item, IsExpanded());
	}
}