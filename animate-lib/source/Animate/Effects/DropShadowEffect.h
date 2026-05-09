#pragma once

#include "GraphicEffect.h"

namespace Animate::Effect {
	class DropShadowEffect : public GraphicEffect {
	public:
		virtual Type EffectType() override {
			return Type::DropShadow;
		};

	public:
		void SetColor(ColorAlpha color);
		ColorAlpha GetColor() const;

		void SetDistance(float value);
		float GetDistance() const;

		void SetAngle(float value);
		float GetAngle() const;

		void SetStrength(uint32_t value);
		uint32_t GetStrength() const;

	private:
		ColorAlpha m_color;
		float m_distance = 4.0f;
		float m_angle = 0.0f;
		uint32_t m_strength = 100;
	};
}
