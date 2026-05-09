#include "PicObject.h"

#include "Animate/XFL/DOM/Effect/GraphicEffect.h"
#include "Animate/Effects/GlowEffect.h"
#include "Animate/Effects/DropShadowEffect.h"
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
		DOM::GraphicEffect writer;
		writer.type = effect.EffectType();

		writer.blurX = effect.GetBlurX();
		writer.blurY = effect.GetBlurY();
		writer.quality = (uint32_t)effect.GetQuality();
		writer.strength = (float)effect.GetStrength() / 100.f;

		switch (effect.EffectType()) {
		case Effect::GraphicEffect::Type::Glow:
		{
			Effect::GlowEffect& glow = (Effect::GlowEffect&)effect;
			writer.color = glow.GetColor();
		}
		break;
		case Effect::GraphicEffect::Type::DropShadow:
		{
			Effect::DropShadowEffect& dropShadow = (Effect::DropShadowEffect&)effect;

			writer.color = dropShadow.GetColor();
			writer.distance = dropShadow.GetDistance();
			writer.angle = dropShadow.GetAngle();
		}
		break;
		default:
			throw wk::Exception("Not implemented");
		}

		XFL::XFLWriter filter(root, writer);
	}
}

