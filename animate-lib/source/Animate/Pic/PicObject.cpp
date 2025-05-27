#include "PicObject.h"

#include "Animate/Document/SketchDocument.h"

namespace Animate::Pic
{
	void Object::SetOwner(Document::SketchDocument& document)
	{
		m_owner = &document;
		m_parent = nullptr;
	}

	void Object::SetOwner(Object& parent)
	{
		m_owner = &parent.OwnerDoc();
		m_parent = &parent;
	}

	Document::SketchDocument& Object::OwnerDoc() const
	{
		assert(m_owner != nullptr);
		return *m_owner;
	}

	void Object::WriteXFLMatrix(XFL::XFLWriter& root) const
	{
		Matrix matrix;
		if (!GetMatrix(matrix)) return;
		if (matrix == Matrix::Identity()) return;

		auto writer = root.CreateProperty(DOM::PropTag::Matrix);
		DOM::DOMMatrix domMatrix(matrix);
		XFL::XFLWriter(writer, domMatrix);
	}
}

