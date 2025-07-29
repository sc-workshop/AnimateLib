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

		virtual bool GetMatrix(Matrix& matrix) const override {
			matrix = m_matrix;
			return true;
		}

		virtual bool SetMatrix(const Matrix& matrix) override {
			m_matrix = matrix;
			return true;
		}

		virtual Object* CloneObject()
		{
			return new Group(*this);
		}

	private:
		Matrix m_matrix;
	};
}