#include "DOMItem.h"

#include "XFL/Writer.h"

namespace Animate::DOM
{
	void DOMItem::SetAttributes(XFL::XFLWriter& writer)
	{
		writer.WriteAttr(
			GetPropName(Props::Name), name, Default_Name
		);

		writer.WriteAttr(
			GetPropName(Props::ItemID), itemId, Default_ItemID
		);
	}
}