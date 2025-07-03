#include "PicLayer.h"

namespace Animate::Pic
{
	void Layer::WriteXFL(XFL::XFLWriter& root, uint32_t /*index*/) const
	{
		DOM::DOMLayer layer;
		layer.name = m_name;

		XFL::XFLWriter writer(root, layer);

		auto frames = writer.CreateProperty(DOM::PropTag::Frames);

		uint32_t index = 0;
		for (const Frame& frame : *this)
		{
			frame.WriteXFL(frames, index++);
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

