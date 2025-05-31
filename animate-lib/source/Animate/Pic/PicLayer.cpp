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

	size_t Layer::GetNumFrames()
	{
		size_t result = 0;
		for (auto& layer : *this)
		{
			result += layer.GetDuration();
		}
		return result;
	}

	Frame& Layer::CreateFrame()
	{
		Frame& frame = AddChild<Frame>();
		return frame;
	}

	void Layer::Create()
	{
		//m_childrens.clear();
		//CreateFrame();
	}
}

