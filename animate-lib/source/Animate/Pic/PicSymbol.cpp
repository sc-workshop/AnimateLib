#include "PicSymbol.h"

#include "Animate/Library/LibraryItem/DocumentPage.h"

#include "Animate/XFL/DOM/Instance/DOMSymbolInstance.h"
#include "Animate/XFL/DOM/Instance/DOMBitmapInstance.h"

namespace Animate::Pic
{
	Symbol::Symbol()
	{
		m_effect_instance = &m_graphic_effect;
	}

	void Symbol::WriteXFL(XFL::XFLWriter& root, uint32_t) const
	{
		if (!m_page) return;

		DOM::DOMSymbolInstance instance;
		instance.libraryItemName = XFL::XFLWriter::MakePrefferedPath(m_page->GetItemPath());
		instance.name = m_name;
		instance.type = m_type;

		XFL::XFLWriter writer(root, instance);
		WriteXFLMatrix(writer);
		m_graphic_effect.WriteXFL(writer);
	}
}

