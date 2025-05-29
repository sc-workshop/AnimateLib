#pragma once

#include "PicObject.h"

#include "Animate/XFL/DOM/Timeline/DOMFrame.h"

namespace Animate::Library
{
	class MediaBits;
}

namespace Animate::Pic
{
	class Bitmap;
}

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

	public:
		PicIterator<Object> begin() { return PicIterator<Object>::CreateBegin(*this); }
		PicIterator<Object> end() { return PicIterator<Object>::CreateEnd(*this); }

	public:
		Bitmap& AddBitmapChildren(Library::MediaBits& bits);

	protected:
		virtual Object* CloneObject()
		{
			return new Frame(*this);
		}

	private:
		uint32_t m_duration = 0;
	};
}