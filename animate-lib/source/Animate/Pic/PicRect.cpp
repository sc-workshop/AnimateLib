#include "PicRect.h"

namespace Animate::Pic
{
	void Rectangle::WriteXFL(XFL::XFLWriter& writer, uint32_t) const
	{
		DOM::RectangleObject obj;
		obj.rectangle = m_rectangle;

		XFL::XFLWriter root(writer, obj);
		auto style_writer = root.CreateProperty(DOM::PropTag::Fill);
		WriteXFLStyle(style_writer, m_style);
	}
}