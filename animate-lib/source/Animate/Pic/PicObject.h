#pragma once

#include "assert.h"
#include "core/memory/ref.h"

#include "PicIterator.h"

#include "Animate/XFL/Writer.h"
#include "Animate/XFL/DOM/Math/Matrix.h"
#include "Animate/TypeTraits.h"

namespace Animate::Document
{
	class SketchDocument;
}

namespace Animate::Pic
{
	/// <summary>
	/// PIC is probably means something like "Program interaction control"
	/// But overall its just a bunch of "conrol classes" that allow you to interact with layers, frames and other objects
	/// </summary>
	class Object
	{
	public:
		using Childrens = Container<wk::Ref<Object>>;

	public:
		template <typename T>
		friend class PicIterator;

	public:
		virtual ~Object() = default;
		void SetOwner(Object& parent);
		void SetOwner(Document::SketchDocument& document);

	public:
		virtual bool IsPicPage() const { return false; };
		virtual bool IsPicShape() const { return false; };
		virtual bool IsPicFrame() const { return false; };
		virtual bool IsPicLayer() const { return false; };
		virtual bool IsPicSymbol() const { return false; };
		virtual bool IsPicButton() const { return false; };
		virtual bool IsPicText() const { return false; };
		virtual bool IsPicBitmap() const { return false; };
		virtual bool IsPicTweenable() const { return false; };

		Document::SketchDocument& OwnerDoc() const;
		Object* Parent() { return m_parent;  };

		Object* Clone()
		{
			Object* result = CloneObject();
			result->CloneChildrens();
			return result;
		}

	public:
		virtual void WriteXFL(XFL::XFLWriter& /*writer*/, uint32_t /*index*/) const {};

	public:
		virtual bool GetMatrix(Matrix& /*matrix*/) const { return false; }
		virtual bool SetMatrix(const Matrix& /*matrix*/) { return false; }
		void WriteXFLMatrix(XFL::XFLWriter& wrtier) const;
	
	protected:
		template<typename T = Object, typename ... Args>
		T& AddChild(Args&&... args)
		{
			auto object = wk::CreateRef<T>(std::forward<Args>(args)...);
			object->SetOwner(*this);
			m_childrens.push_back(object);
			return *object;
		}

		template<typename T = Object, typename ... Args>
		T& AddChildAt(size_t index, Args&&... args)
		{
			auto object = wk::CreateRef<T>(std::forward<Args>(args)...);
			object->SetOwner(*this);
			m_childrens.insert(m_childrens.begin() + index, object);
			return *object;
		}

		template<typename T = Object>
		T& AddChildAt(size_t index, T* ptr)
		{
			auto object = wk::Ref<T>(ptr);
			object->SetOwner(*this);
			m_childrens.insert(m_childrens.begin() + index, object);
			return *object;
		}

		template<typename T = Object>
		T& ChildAt(size_t index)
		{
			auto& object = m_childrens[index];
			return (T&)*object;
		}

		template<typename T = Object>
		const T& ChildAt(size_t index) const
		{
			const auto& object = m_childrens[index];
			return (const T&)*object;
		}

		size_t ChildrenCount() const { return m_childrens.size(); }

		virtual Object* CloneObject() = 0;

		void CloneChildrens()
		{
			for (size_t i = 0; ChildrenCount() > i; i++)
			{
				m_childrens[i] = wk::Ref<Object>(m_childrens[i]->Clone());
			}
		}

	protected:
		Childrens m_childrens;

	private:
		Document::SketchDocument* m_owner;
		Object* m_parent = nullptr;
	};
}