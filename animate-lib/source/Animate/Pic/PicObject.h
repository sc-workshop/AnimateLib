#pragma once

#include "assert.h"
#include "core/memory/ref.h"

#include "PicIterator.h"

#include "Animate/XFL/Writer.h"
#include "Animate/XFL/DOM/Math/Matrix.h"
#include "Animate/Library/Properties/GraphicEffectInstance.h"
#include "Animate/Effects/GraphicEffect.h"
#include "Animate/TypeTraits.h"

namespace Animate::Document
{
	class SketchDocument;
}

namespace Animate::Pic
{
	class Layer;
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
		friend Layer;

	public:
		using Childrens = Container<wk::Ref<Object>>;

	public:
		template <typename T, typename TP>
		friend class PicIterator;

	public: // Constructor
		virtual ~Object() = default;
		virtual void SetOwner(Object& parent);
		virtual void SetOwner(Document::SketchDocument& document);

	public: // Object types
		virtual bool IsPicPage() const { return false; };
		virtual bool IsPicShape() const { return false; };
		virtual bool IsPicFrame() const { return false; };
		virtual bool IsPicLayer() const { return false; };
		virtual bool IsPicSymbol() const { return false; };
		virtual bool IsPicButton() const { return false; };
		virtual bool IsPicText() const { return false; };
		virtual bool IsPicBitmap() const { return false; };
		virtual bool IsPicTweenable() const { return false; };
		virtual bool IsPicGroup() const { return false; };

		Document::SketchDocument* OwnerDoc() const;
		Object* Parent() const { return m_parent;  };

		Object* Clone() const
		{
			Object* result = CloneObject();
			result->CloneChildrens();
			return result;
		}

	public: // XFL IO
		virtual void WriteXFL(XFL::XFLWriter& /*writer*/, uint32_t /*index*/) const {};

	public: // Transforms
		virtual Library::GraphicEffectInstance* GetGraphicEffectInstance() { return m_effect_instance; }
		virtual bool GetMatrix(Matrix& /*matrix*/) const { return false; }
		virtual bool SetMatrix(const Matrix& /*matrix*/) { return false; }
		void WriteXFLMatrix(XFL::XFLWriter& wrtier) const;
		void WriteXFLGraphicEffect(XFL::XFLWriter& wrtier, Effect::GraphicEffect& effect) const;

		virtual void SetWidth(float) {};
		virtual void SetHeight(float) {};

	public: // Properties
		virtual void SetPIInstanceName(const String& /*name*/) {};
	
	protected:
		template<typename T = Object, typename ... Args>
		T& AddChild(Args&&... args)
		{
			auto object = wk::CreateRef<T>(std::forward<Args>(args)...);
			object->SetOwner(*this);
			m_childrens.push_back(object);
			return *object;
		}

		Object& AddReference(const Object& obj)
		{
			auto object = wk::Ref<Object>(obj.Clone());
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
			auto& object = m_childrens.at(index);
			return (T&)*object;
		}

		template<typename T = Object>
		const T& ChildAt(size_t index) const
		{
			const auto& object = m_childrens[index];
			return (const T&)*object;
		}

		void MoveChildrens(size_t from, size_t to)
		{
			if (from == to || from >= m_childrens.size() || to >= m_childrens.size())
				return;
			auto object = m_childrens[from];
			m_childrens.erase(m_childrens.begin() + from);
			m_childrens.insert(m_childrens.begin() + to, object);
		}

		bool GetChildrenIndex(const Object& obj, size_t& index) const
		{
			auto it = std::find_if(m_childrens.begin(), m_childrens.end(), [&obj](const wk::Ref<Object>& other) {
				if (other.get() == &obj)
				{
					return true;
				}
				return false;
			});
			
			if (it == m_childrens.end()) return false;
			
			index = std::distance(m_childrens.begin(), it);
			return true;
		}

		size_t ChildrenCount() const { return m_childrens.size(); }

		virtual Object* CloneObject() const = 0;

		void CloneChildrens()
		{
			for (size_t i = 0; ChildrenCount() > i; i++)
			{
				m_childrens[i] = wk::Ref<Object>(m_childrens[i]->Clone());
			}
		}

	protected:
		Childrens m_childrens;
		Library::GraphicEffectInstance* m_effect_instance = nullptr;

	protected:
		Document::SketchDocument* m_owner;
		Object* m_parent = nullptr;
	};
}