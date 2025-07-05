#pragma once

#include "Animate/TypeTraits.h"
#include "Animate/Math/ColorTransform.h"

#include "Animate/XFL/Writer.h"
#include "Animate/XFL/DOM/Math/Color.h"

namespace Animate::Pic
{
	class Object;
}

namespace Animate::Library
{
	class GraphicEffectInstance
	{
	public:
		static void SetColorMatrixForAlpha(ColorTransform& matrix, int16_t alpha);
		static void SetColorMatrixForBrightness(ColorTransform& matrix, int16_t brightness);
		static void SetColorMatrixForTint(ColorTransform& matrix, Color tint, int16_t multiplier);

	public:
		ColorTransform GetColorTransform() const { return m_matrix; };
		void SetColorTransform(const ColorTransform& matrix) { m_matrix = matrix; }

		void SetColorTransforEffectAlpha(int16_t alpha);
		void SetColorTransforEffectBrightness(int16_t brightness);
		void SetColorTransforEffectTint(Color tint, int16_t multiplier);

		void SetColorTransformMode(ColorTransform::Type /*type*/) {}

	public:
		void WriteXFL(XFL::XFLWriter& root) const;

	private:
		ColorTransform m_matrix;
	};
}