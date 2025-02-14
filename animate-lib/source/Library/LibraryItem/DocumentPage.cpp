#include "DocumentPage.h"

#include "Document/SketchDocument.h"
#include "XFL/DOM/Document/Include.h"
#include "XFL/DOM/Items/DOMSymbolItem.h"
#include "XFL/DOM/Document/DOMTimeline.h"

namespace Animate::Library
{
	void DocumentPage::WriteXFL(XFL::XFLFile& /*file*/, XFL::XFLWriter& writer) const
	{
		DOM::Include item;
		item.href = GetItemPath().u16string();
		item.last_modified = m_last_modify_time;
		item.item_id = m_item_id.ToString();
		item.item_icon = (int)m_type;

		XFL::XFLWriter include(writer, item);
	}

	void DocumentPage::WriteXFLSymbol(XFL::XFLFile& file) const
	{
		DOM::DOMSymbolItem item;
		InitializeDOMItem(item);
		item.last_modified = m_last_modify_time;

		XFL::XFLWriter writer(item);
		auto timeline = writer.CreateProperty(DOM::PropTag::Timeline);
		WriteXFLTimeline(timeline);

		file.SaveSymbol(writer, GetItemPath());
	}

	void DocumentPage::WriteXFLTimeline(XFL::XFLWriter& root) const
	{
		DOM::DOMTimeline timeline;
		timeline.name = m_item_name;

		XFL::XFLWriter writer(root, timeline);
	}

	void DocumentPage::CreateSymbol(Document::SketchDocument& root)
	{
		Create(root, false);
	}

	void DocumentPage::Create(Document::SketchDocument& /*root*/, bool /*is_scene*/)
	{
		time(&m_creation_time);
	}
}

