#include "PicLayer.h"

#include "Animate/XFL/DOM/Timeline/DOMLayer.h"

namespace Animate::Pic
{
	void Layer::WriteXFL(XFL::XFLWriter& root, uint32_t /*index*/) const
	{
		DOM::DOMLayer layer;
		layer.name = m_name;
		layer.type = m_type;
		layer.locked = m_locked;
		if (m_parent_layer)
			Parent()->GetChildrenIndex(*m_parent_layer, layer.parentIndex);
			
		XFL::XFLWriter writer(root, layer);

		uint32_t index = 0;
		auto frames = writer.CreateProperty(DOM::PropTag::Frames);
		for (const Frame& frame : *this)
		{
			frame.WriteXFL(frames, index++);
		}
	}

	void Layer::Initialize(const String& name, size_t /*duration*/)
	{
		Create();
		SetName(name);

		//Frame& frame = FirstFrame();
		// TODO: set duration
	}

	void Layer::SetLocked(bool status)
	{
		if (IsFolder())
		{
			// TODO: lock parent layers
		}

		m_locked = status;
	}

	size_t Layer::GetDuration()
	{
		size_t result = 0;
		for (auto& frame : *this)
		{
			result += frame.GetDuration();
		}
		return result;
	}

	Frame& Layer::CreateFrame()
	{
		Frame& frame = AddChild<Frame>();
		return frame;
	}

	Layer* Layer::ClippedBy() const
	{
		if (m_parent_layer == nullptr) return nullptr;

		if (m_parent_layer->IsClipper())
			return m_parent_layer;

		return nullptr;
	}

	void Layer::SetClipper()
	{
		m_type = Type::Clipper;
		SetLocked();
	}

	void Layer::AttachMask(Layer& mask)
	{
		m_parent_layer = &mask;
		SetLocked();
	}

	void Layer::Create()
	{
		//m_childrens.clear();
		//CreateFrame();
	}
}

