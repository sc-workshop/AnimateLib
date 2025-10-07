#pragma once

#include "GraphicEffectInstance.h"
#include "Animate/Effects/GraphicEffect.h"
#include "core/memory/ref.h"

namespace Animate::Library
{
	class AdvancedEffectInstance : public GraphicEffectInstance {
	private:
		using Effect = Animate::Effect::GraphicEffect;
		using EffectVector = std::vector<wk::Ref<Effect>>;

	public:
		virtual ~AdvancedEffectInstance() = default;
		virtual bool SupportsGraphicEffects() override {
			return true;
		}

	public:
		const EffectVector& GetGraphicEffectList() const {
			return m_effects;
		}

		Effect& AddGraphicEffect(Effect::Type type);

	private:
		EffectVector m_effects;
	};
}