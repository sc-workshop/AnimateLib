#include "PicLayer.h"

namespace Animate::Pic
{
	void Layer::WriteXFL(XFL::XFLWriter& writer) const
	{

	}

	void Layer::Initialize(const String& name, size_t duration)
	{
		Create();
		SetName(name);

		Frame& frame = FirstFrame();
		// TODO: set duration
	}

	Frame& Layer::FirstFrame()
	{
		if (m_childrens.empty()) Create();

		auto& firstFrame = ChildAt(0); // TODO: implement and use FindFrame
		assert(!firstFrame.IsPicFrame());

		return (Frame&)firstFrame;
	}

	Frame& Layer::CreateFrame()
	{
		Frame& frame = AddChild<Frame>();
		return frame;
	}

	void Layer::Create()
	{
		m_childrens.clear();
		CreateFrame();
	}
}

