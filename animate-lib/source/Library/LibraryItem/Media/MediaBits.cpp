#include "MediaBits.h"

#include "XFL/DOM/DOMItem.h"

namespace Animate::Library
{
    void MediaBits::WriteXFL(XFL::XFLWriter& writer) const
    {
        DOM::DOMItem item(DOM::DOMItem::Type::Bitmap);
        item.name = XFL::XFLWriter::MakePrefferedPath(GetLibraryItemPath());
        item.itemId = m_item_id.ToString();

        writer.WriteDOMBitmapItem(item);
    }
}