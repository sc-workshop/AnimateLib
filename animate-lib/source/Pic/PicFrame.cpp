#include "PicFrame.h"

namespace Animate::Pic
{
	void Frame::WriteXFL(XFL::XFLWriter& root, uint32_t index) const
	{
		DOM::DOMFrame frame;
		frame.duration = m_duration;
		frame.index = index;

		XFL::XFLWriter writer(root, frame);

		auto elements = writer.CreateProperty(DOM::PropTag::Elements);
		for (uint32_t i = 0; ChildrenCount() > i; i++)
		{
			auto& element = ChildAt(i);
			element.WriteXFL(elements, i);
		}
	}

}
