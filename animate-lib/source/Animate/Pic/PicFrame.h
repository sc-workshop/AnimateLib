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
		enum class LabelType {
			None = 0,
			Name,
			Comment,
			Anchor
		};

	public:
		Frame();

	public:
		virtual bool IsPicFrame() const override { return true; };
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t index) const override;

	public:
		uint32_t GetDuration() const { return m_duration; }
		void SetDuration(uint32_t duration) { m_duration = duration; }
		void SetLabel(String label, LabelType type);

	public:
		String GetLabel();
		LabelType GetLabelType();

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
		virtual Object* CloneObject() override
		{
			return new Frame(*this);
		}

	private:
		String m_label = "";
		LabelType m_labelType = LabelType::None;
		uint32_t m_duration = 1;
		Library::GraphicEffectInstance m_graphic_effect;
	};
}