#include "PicLayer.h"

namespace Animate::Pic
{
	void Layer::WriteXFL(XFL::XFLWriter& root, uint32_t /*index*/) const
	{
		DOM::DOMLayer layer;
		layer.name = m_name;

		XFL::XFLWriter writer(root, layer);

		auto frames = writer.CreateProperty(DOM::PropTag::Frames);
		for (uint32_t i = 0; ChildrenCount() > i; i++)
		{
			auto& frame = ChildAt<Frame>(i);
			frame.WriteXFL(frames, i);
		}
	}

	void Layer::Initialize(const String& name, size_t duration)
	{
		Create();
		SetName(name);

		//Frame& frame = FirstFrame();
		// TODO: set duration
	}

	Frame& Layer::FirstFrame()
	{
		if (m_childrens.empty()) Create();

		auto& firstFrame = ChildAt(0); // TODO: implement and use FindFrame
		assert(firstFrame.IsPicFrame());

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

