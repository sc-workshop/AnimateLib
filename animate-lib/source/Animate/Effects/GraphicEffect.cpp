#include "GraphicEffect.h"

#include "core/exception/exception.h"
#include "GlowEffect.h"

namespace Animate::Effect {
	GraphicEffect* GraphicEffect::CreateEffect(Type type)
	{
		switch (type) {
		case Type::Glow:
			return new GlowEffect();
		default:
			throw wk::Exception("Graphic effect instance not implemented: " + std::to_string((uint32_t)type));
		}
	}
}

