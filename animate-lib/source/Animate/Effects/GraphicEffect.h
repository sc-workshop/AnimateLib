#pragma once

#include "Animate/XFL/Writer.h"

namespace Animate::Pic {
	class Object;
}

namespace Animate::Effect {
	class GraphicEffect {
	public:
		friend Animate::Pic::Object;

		enum class Type {
			DropShadow = 0,
			Blur,
			Glow,
			Bevel,
			GradientFlow,
			AdjustColor,
			GradientBevel
		};

		enum class Quality {
			None = 0,
			Low,
			Medium,
			High
		};

	public:
		virtual ~GraphicEffect() = default;
		virtual Type EffectType() = 0;

		void SetBlurX(uint8_t value) { m_blurX = value; }
		void SetBlurY(uint8_t value) { m_blurY = value; }
		void SetQuality(Quality value) { m_quality = value; }
		void SetStrength(float value) { m_strength = value; }

	public:
		static GraphicEffect* CreateEffect(Type type);

	protected:
		uint8_t m_blurX = 4;
		uint8_t m_blurY = 4;
		Quality m_quality = Quality::Low;
		float m_strength = 1.f;
	};
}