#pragma once

#include "PicObject.h"

#include "XFL/DOM/Timeline/DOMFrame.h"

namespace Animate::Pic
{
	class Frame : public Object
	{
	public:
		using Object::Object;

	public:
		virtual bool IsPicFrame() const override { return true; };
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t index) const override;

	public:
		uint32_t GetDuration() const { return m_duration; }
		void SetDuration(uint32_t duration) { m_duration = duration; }

	private:
		uint32_t m_duration = 0;
	};
}