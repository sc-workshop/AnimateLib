#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class DOMMatrix : public DOMElement
	{
	public:
		DOMMatrix(const Matrix& matrix) : m_matrix(matrix)
		{
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::Matrix;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			auto& identity = Matrix::Identity();

			if (twip_scale)
				writer.WriteAttr("a", m_matrix.a * 20.f, 20.f);
			else
				writer.WriteAttr("a", m_matrix.a, identity.a);

			writer.WriteAttr("b", m_matrix.b, identity.b);
			writer.WriteAttr("c", m_matrix.c, identity.c);

			if (twip_scale)
				writer.WriteAttr("d", m_matrix.d * 20.f, 20.f);
			else
				writer.WriteAttr("d", m_matrix.d, identity.d);

			writer.WriteAttr("tx", m_matrix.tx, identity.tx);
			writer.WriteAttr("ty", m_matrix.ty, identity.ty);
		}

	public:
		bool twip_scale = false;
		const Matrix& m_matrix;
	};
}