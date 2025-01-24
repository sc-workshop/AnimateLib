#include "MediaElem.h"

#include "Document/SketchDocument.h"
#include "XFL/DOM/DOMItem.h"

namespace Animate::Library
{
	MediaElem::MediaElem(Document::SketchDocument& document, const std::u16string& name) : LibraryItem(document, name)
	{
		time_t creation_time;
		time(&creation_time);

		m_media_filename = "M " + std::to_string(MediaCounter++) + " " + std::to_string(creation_time);
	}

	time_t MediaElem::GetModDateForLibrary() const
	{
		return m_last_modify;
	}

	void MediaElem::SetModDateForLibrary(time_t time)
	{
		m_last_modify = time;
	}
}