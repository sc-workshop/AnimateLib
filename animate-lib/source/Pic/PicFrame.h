#pragma once

#include "PicObject.h"

namespace Animate::Pic
{
	class Frame : public Object
	{
	public:
		using Object::Object;

	public:
		virtual bool IsPicFrame() const override { return true; };

	public:
		uint32_t GetDuration() const { return m_duration; }
		void SetDuration(uint32_t duration) { m_duration = duration; }

	private:
		uint32_t m_duration = 0;
	};
}