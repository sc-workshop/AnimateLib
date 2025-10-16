#include "PicObject.h"

#include "Animate/XFL/DOM/Effect/GraphicEffect.h"
#include "Animate/Effects/GlowEffect.h"
#include "Animate/Document/SketchDocument.h"

namespace Animate::Pic
{
	void Object::SetOwner(Document::SketchDocument& document)
	{
		m_owner = &document;
		for (auto& child : m_childrens)
		{
			child->SetOwner(document);
		}
	}

	void Object::SetOwner(Object& parent)
	{
		m_parent = &parent;

		auto doc = parent.OwnerDoc();
		if (doc) SetOwner(*doc);
	}

	Document::SketchDocument* Object::OwnerDoc() const
	{
		return m_owner;
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

	void Object::WriteXFLGraphicEffect(XFL::XFLWriter& root, Effect::GraphicEffect& effect) const
	{
		switch (effect.EffectType()) {
		case Effect::GraphicEffect::Type::Glow:
		{
			Effect::GlowEffect& glow = (Effect::GlowEffect&)effect;
			DOM::GraphicEffect writer;
			writer.type = effect.EffectType();
			writer.blurX = effect.m_blurX;
			writer.blurY = effect.m_blurY;
			writer.quality = (uint32_t)effect.m_quality;
			writer.color = glow.GetColor();
			writer.strength = effect.m_strength;

			XFL::XFLWriter filter(root, writer);
		}
		break;
		default:
			throw wk::Exception("Not implemented");
		}
	}
}

