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
		instance.blendMode = m_graphic_effect.GetXFLBlendMode();

		XFL::XFLWriter writer(root, instance);
		WriteXFLMatrix(writer);

		if (m_graphic_effect.GetColorTransformMode() != ColorTransform::Type::None)
		{
			XFL::XFLProp color = writer.CreateProperty(DOM::PropTag::Color);
			m_graphic_effect.WriteXFLColor(color);
		}
	}
}

