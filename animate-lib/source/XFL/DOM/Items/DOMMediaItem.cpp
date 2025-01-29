#include "DOMMediaItem.h"

namespace Animate::DOM
{
	DOMMediaItem::DOMMediaItem(Type type)
	{
		switch (type)
		{
		case Type::Bitmap:
			m_tag = ElementTag::DOMBitmapItem;
			break;
		default:
			throw wk::Exception();
		}
	}

	void DOMMediaItem::SetAttributes(XFL::XFLWriter& writer)
	{
		DOMItem::SetAttributes(writer);


	}
}

