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

		void SetBlurX(float value) {
			if (value >= 0.0 && value <= 255.0)
				m_blurX = value;
		}
		float GetBlurX() const { return m_blurX; }

		void SetBlurY(float value) {
			if (value >= 0.0 && value <= 255.0)
				m_blurY = value;
		}
		float GetBlurY() const { return m_blurY; }

		void SetQuality(Quality value) { m_quality = value; }
		Quality GetQuality() const { return m_quality; }

		void SetStrength(uint32_t value) {
			if (value <= 25500)
				m_strength = value;
		}
		uint32_t GetStrength() const { return m_strength; }

	public:
		static GraphicEffect* CreateEffect(Type type);

	protected:
		float m_blurX = 4;
		float m_blurY = 4;
		Quality m_quality = Quality::Low;
		uint32_t m_strength = 100;
	};
}
