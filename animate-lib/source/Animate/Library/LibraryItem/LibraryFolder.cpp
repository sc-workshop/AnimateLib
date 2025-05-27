#include "LibraryFolder.h"

#include "Animate/Document/SketchDocument.h"

namespace Animate::Library
{
	void LibraryFolder::WriteXFL(XFL::XFLFile& /*file*/, XFL::XFLWriter& root) const
	{
		DOM::DOMFolderItem item;
		InitializeDOMItem(item);

		XFL::XFLWriter writer(root, item);
	}

	void LibraryFolder::InitializeDOMItem(DOM::DOMFolderItem& item) const
	{
		LibraryItem::InitializeDOMItem(item);
		item.is_expanded = IsExpanded();
	}
}