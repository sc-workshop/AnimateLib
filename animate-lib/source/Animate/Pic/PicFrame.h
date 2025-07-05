#pragma once

#include "PicObject.h"

#include "Animate/XFL/DOM/Timeline/DOMFrame.h"

namespace Animate::Library
{
	class MediaBits;
	class DocumentPage;
}

namespace Animate::Pic
{
	class Bitmap;
	class Symbol;
	class Shape;
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
		template<typename T = Object, typename ... Args>
		T& AddFrameElement(Args&&... args)
		{
			return AddChild<T>(std::forward<Args>(args)...);
		}

		Bitmap& AddBitmapChildren(Library::MediaBits& bits);
		Symbol& AddSymbolChildren(Library::DocumentPage& page);

	public:
		// Access operators
		size_t FramesCount() const { return ChildrenCount(); }
		Iterator<Object> begin() { return Iterator<Object>::CreateBegin(*this); }
		Iterator<Object> end() { return Iterator<Object>::CreateEnd(*this); }
		ConstIterator<Object> begin() const { return ConstIterator<Object>::CreateBegin(*this); }
		ConstIterator<Object> end() const { return ConstIterator<Object>::CreateEnd(*this); }
		Object& operator [](size_t index) { return ChildAt<Object>(index); }

	protected:
		virtual Object* CloneObject()
		{
			return new Frame(*this);
		}

	private:
		uint32_t m_duration = 1;
	};
}