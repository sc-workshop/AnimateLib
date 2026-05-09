#include "DropShadowEffect.h"

namespace Animate::Effect {
	void DropShadowEffect::SetColor(ColorAlpha color) { m_color = color; }
	ColorAlpha DropShadowEffect::GetColor() const { return m_color; }

	void DropShadowEffect::SetDistance(float value) {
		if (value >= -255.f && value <= 255.f)
			m_distance = value;
	}
	float DropShadowEffect::GetDistance() const { return m_distance; }
		
	void DropShadowEffect::SetAngle(float value) {
		if (value >= 0.f && value <= 360.f)
			m_angle = value;
	}
	float DropShadowEffect::GetAngle() const { return m_angle; }

	void DropShadowEffect::SetStrength(uint32_t value) {
		if (value <= 25500)
			m_strength = value;
	}
	uint32_t DropShadowEffect::GetStrength() const { return m_strength; }
}
