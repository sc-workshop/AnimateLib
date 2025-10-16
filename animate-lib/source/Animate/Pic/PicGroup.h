#pragma once

#include "PicObject.h"

namespace Animate::Pic
{
	class Group : public Object
	{
	public:
		virtual bool IsPicGroup() const override { return true; }

	public:
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t /*index*/) const override;

	public:
		template<typename T = Object, typename ... Args>
		T& AddElement(Args&&... args)
		{
			return AddChild<T>(std::forward<Args>(args)...);
		}

		Object& AddElementReference(const Object& obj)
		{
			return AddReference(obj);
		}

		virtual bool GetMatrix(Matrix& matrix) const override {
			matrix = m_matrix;
			return true;
		}

		virtual bool SetMatrix(const Matrix& matrix) override {
			m_matrix = matrix;
			return true;
		}

		virtual Object* CloneObject() const override
		{
			return new Group(*this);
		}

	public:
		Iterator<Object> begin() { return Iterator<Object>::CreateBegin(*this); }
		Iterator<Object> end() { return Iterator<Object>::CreateEnd(*this); }
		ConstIterator<Object> begin() const { return ConstIterator<Object>::CreateBegin(*this); }
		ConstIterator<Object> end() const { return ConstIterator<Object>::CreateEnd(*this); }

	private:
		Matrix m_matrix;
	};
}