#include "PicObject.h"

#include "Document/SketchDocument.h"

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
}

