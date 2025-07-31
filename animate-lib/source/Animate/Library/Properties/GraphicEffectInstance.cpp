#include "GraphicEffectInstance.h"

namespace Animate::Library
{
	void GraphicEffectInstance::SetColorMatrixForAlpha(ColorTransform& matrix, int16_t alpha)
	{
		if (alpha < 0) return;

		matrix.multiply_red = 0xFF;
		matrix.multiply_green = 0xFF;
		matrix.multiply_blue = 0xFF;
		matrix.multiply_alpha = 0xFF;

		matrix.offset_red = 0;
		matrix.offset_green = 0;
		matrix.offset_blue = 0;
		matrix.offset_alpha = 0;

		matrix.offset_alpha = ((alpha << 8) | 50) / 100;
		matrix.multiplier = alpha;
		matrix.transform_type = ColorTransform::Type::Alpha;
	}

	void GraphicEffectInstance::SetColorMatrixForBrightness(ColorTransform& matrix, int16_t brightness)
	{
		int16_t normalized = brightness + 100;
		if (normalized <= 200)
		{
			int16_t factor = 0;
			if (brightness > 0)
			{
				factor = (255 * brightness + 50) / 100;
			}

			matrix.multiply_red = factor;
			matrix.multiply_green = factor;
			matrix.multiply_blue = factor;
			matrix.multiply_alpha = 0xFF;

			int16_t offset = (normalized * 256 + 50) / 100;
			matrix.offset_red = offset;
			matrix.offset_green = offset;
			matrix.offset_blue = offset;
			matrix.offset_alpha = 0;

			matrix.multiplier = brightness;
			matrix.transform_type = ColorTransform::Type::Brightness;
		}
	}

	void GraphicEffectInstance::SetColorMatrixForTint(ColorTransform& matrix, Color tint, int16_t multiplier)
	{
		if (multiplier <= 100)
		{
			int16_t offset = (255 * (100 - multiplier) + 50) / 100;

			matrix.multiply_alpha = 0xFF;
			matrix.offset_red = offset;
			matrix.offset_green = offset;
			matrix.offset_blue = offset;

			int16_t multiply = 5243 * (multiplier * tint.r + 50);
			matrix.multiply_red = (multiply >> 31) + (multiply >> 19);
			matrix.multiply_green = (multiplier * tint.g + 50) / 100;
			matrix.multiply_blue = (multiplier * tint.g + 50) / 100;
			matrix.offset_alpha = tint.b + ((multiply << 16) | (tint.g << 8)) - 0x1000000;

			matrix.multiplier = multiplier;
			matrix.transform_type = ColorTransform::Type::Tint;
			matrix.tint = tint;
		}
	}

	void GraphicEffectInstance::SetColorTransforEffectAlpha(int16_t alpha)
	{
		if (m_matrix.offset_alpha == alpha) return;

		ColorTransform matrix;
		GraphicEffectInstance::SetColorMatrixForAlpha(matrix, alpha);
		SetColorTransform(matrix);

		SetColorTransformMode(matrix.transform_type);
	}

	void GraphicEffectInstance::SetColorTransforEffectBrightness(int16_t brightness)
	{
		if (m_matrix.multiplier == brightness) return;

		ColorTransform matrix;
		GraphicEffectInstance::SetColorMatrixForBrightness(matrix, brightness);
		SetColorTransform(matrix);

		SetColorTransformMode(matrix.transform_type);
	}

	void GraphicEffectInstance::SetColorTransforEffectTint(Color tint, int16_t multiplier)
	{
		if (m_matrix.multiplier == multiplier && m_matrix.tint == tint) return;

		ColorTransform matrix;
		GraphicEffectInstance::SetColorMatrixForTint(matrix, tint, multiplier);
		SetColorTransform(matrix);

		SetColorTransformMode(matrix.transform_type);
	}

	void GraphicEffectInstance::WriteXFLColor(XFL::XFLWriter& root) const
	{
		DOM::Color color;

		// TODO: handle other transform types
		switch (m_matrix.transform_type)
		{
		case ColorTransform::Type::Alpha:
			break;
		case ColorTransform::Type::Brightness:
			break;
		case ColorTransform::Type::Tint:
			break;
		default:
			color.alpha_multiplier = m_matrix.multiply_alpha / 255.f;
			color.red_multiplier = m_matrix.multiply_red / 255.f;
			color.green_multiplier = m_matrix.multiply_green / 255.f;
			color.blue_multiplier = m_matrix.multiply_blue / 255.f;
			color.alpha_offset = m_matrix.offset_alpha;
			color.red_offset = m_matrix.offset_red;	
			color.green_offset = m_matrix.offset_green;
			color.blue_offset = m_matrix.offset_blue;
			break;
		}
		

		XFL::XFLWriter writer(root, color);
	}
}

