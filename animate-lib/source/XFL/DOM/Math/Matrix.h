#pragma once

#include <string>
#include <array>

#include "XFL/DOM/DOMElement.h"

#include "TypeTraits.h"

namespace Animate::DOM
{
	class DOMMatrix : public DOMElement
	{
	public:
		DOMMatrix(Matrix& matrix) : m_matrix(matrix)
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

			writer.WriteAttr("a", m_matrix.a, identity.a);
			writer.WriteAttr("b", m_matrix.b, identity.b);
			writer.WriteAttr("c", m_matrix.c, identity.c);
			writer.WriteAttr("d", m_matrix.d, identity.d);
			writer.WriteAttr("tx", m_matrix.tx, identity.tx);
			writer.WriteAttr("ty", m_matrix.ty, identity.ty);
		}

	public:
		Matrix& m_matrix;
	};
}