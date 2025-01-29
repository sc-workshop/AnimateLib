#include "MediaElem.h"

#include "Document/SketchDocument.h"
#include "XFL/DOM/Items/DOMItem.h"
#include "XFL/DOM/Items/DOMMediaItem.h"

namespace Animate::Library
{
	MediaElem::MediaElem(Document::SketchDocument& document, const std::u16string& name) : LibraryItem(document, name)
	{
	}

	void MediaElem::Create()
	{
		time_t creation_time;
		time(&creation_time);

		m_media_filename = "M " + std::to_string(MediaCounter++) + " " + std::to_string(creation_time) + ".dat";
	}

	void MediaElem::UpdateFromSource()
	{
		time(&m_last_source_update);
	}

	void MediaElem::InitializeDOMItem(DOM::DOMMediaItem& item) const
	{
		LibraryItem::InitializeDOMItem((DOM::DOMItem&)item);

		item.source_last_imported = m_last_source_update;
	}
}