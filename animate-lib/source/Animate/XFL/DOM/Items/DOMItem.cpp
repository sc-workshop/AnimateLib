#include "DOMItem.h"

#include "Animate/XFL/Writer.h"

namespace Animate::DOM
{
	void DOMItem::SetAttributes(XFL::XFLWriter& writer)
	{
		writer.WriteAttr(
			GetPropName(Props::Name), name
		);

		writer.WriteAttr(
			GetPropName(Props::ItemID), itemId
		);
	}
}