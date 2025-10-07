#pragma once

#include "GraphicEffect.h"

namespace Animate::Effect {
	class GlowEffect : public GraphicEffect {
	public:
		virtual Type EffectType() override {
			return Type::Glow;
		};

	public:
		void SetColor(ColorAlpha color) { m_color = color; }
		ColorAlpha GetColor() const { return m_color; }

	private:
		ColorAlpha m_color;
	};
}