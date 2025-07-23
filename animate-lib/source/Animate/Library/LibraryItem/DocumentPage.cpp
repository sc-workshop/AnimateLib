#include "DocumentPage.h"

#include "assert.h"
#include "Animate/Document/SketchDocument.h"
#include "Animate/XFL/DOM/Document/Include.h"
#include "Animate/XFL/DOM/Items/DOMSymbolItem.h"
#include "Animate/XFL/DOM/Timeline/DOMTimeline.h"

namespace Animate::Library
{
	void DocumentPage::WriteXFL(XFL::XFLFile& /*file*/, XFL::XFLWriter& root) const
	{
		DOM::Include item;
		item.href = GetItemPath();
		item.last_modified = m_last_modify_time;
		item.item_id = m_item_id.ToString();

		switch (m_type)
		{
		case Animate::Library::DocumentPage::SymbolType::Graphic:
			item.item_icon = 1;
			break;
		default:
			break;
		}

		XFL::XFLWriter writer(root, item);
	}

	void DocumentPage::WriteXFLSymbol(XFL::XFLFile& file) const
	{
		DOM::DOMSymbolItem item;
		InitializeDOMItem(item);
		item.last_modified = m_last_modify_time;
		item.symbol_type = (size_t)m_type;

		XFL::XFLWriter writer(item);
		auto timeline = writer.CreateProperty(DOM::PropTag::Timeline);
		WriteXFLTimeline(timeline);

		file.SaveSymbol(writer, GetItemPath());
	}

	void DocumentPage::WriteXFLTimeline(XFL::XFLWriter& root) const
	{
		DOM::DOMTimeline timeline;
		timeline.name = m_item_name;

		// TODO guides and other stuff

		XFL::XFLWriter writer(root, timeline);
		assert(m_page != nullptr);

		auto layers = writer.CreateProperty(DOM::PropTag::Layers);
		m_page->WriteXFL(layers, 0);
	}

	Pic::Page& DocumentPage::GetPage() const
	{
		assert(m_page != nullptr);
		return *m_page;
	}

	void DocumentPage::CreateSymbol(Document::SketchDocument& root)
	{
		Create(root, false);
		m_page = Pic::Page::Create(*this);
	}

	void DocumentPage::Create(Document::SketchDocument& /*root*/, bool /*is_scene*/)
	{
		time(&m_creation_time);
	}

	void DocumentPage::InitializeSymbol(const Library::DocumentPage::SymbolType type, const Library::LibraryItemID& parent)
	{
		Library::LibraryItemID symbol_id;
		symbol_id.GenerateUniqueID();
		SetID(symbol_id);
		SetParentID(parent);
		CreateSymbol(m_document);
		m_type = type;
	}
}

