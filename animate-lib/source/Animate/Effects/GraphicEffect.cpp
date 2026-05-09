#include "GraphicEffect.h"

#include "core/exception/exception.h"
#include "GlowEffect.h"
#include "DropShadowEffect.h"

namespace Animate::Effect {
	GraphicEffect* GraphicEffect::CreateEffect(Type type)
	{
		switch (type) {
		case Type::Glow:
			return new GlowEffect();
		case Type::DropShadow:
			return new DropShadowEffect();
		default:
			throw wk::Exception("Graphic effect instance not implemented: " + std::to_string((uint32_t)type));
		}
	}
}
