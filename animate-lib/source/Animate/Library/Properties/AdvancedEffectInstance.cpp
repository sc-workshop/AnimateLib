#include "AdvancedEffectInstance.h"

namespace Animate::Library {
	AdvancedEffectInstance::Effect& AdvancedEffectInstance::AddGraphicEffect(Effect::Type type)
	{
		wk::Ref<AdvancedEffectInstance::Effect> result(AdvancedEffectInstance::Effect::CreateEffect(type));
		m_effects.push_back(result);
		return *result;
	}
}

