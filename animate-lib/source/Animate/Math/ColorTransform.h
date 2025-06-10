#pragma once

#include "Animate/TypeTraits.h"

namespace Animate
{
	class ColorTransform
	{
	public:
		enum class Type
		{
			None,
			Brightness,
			Tint,
			Special,
			Alpha
		};

	public:
		int16_t offset_red = 0;
		int16_t multiply_red = 255;

		int16_t offset_green = 0;
		int16_t multiply_green = 255;

		int16_t offset_blue = 0;
		int16_t multiply_blue = 255;

		int16_t offset_alpha = 0;
		int16_t multiply_alpha = 255;

		int16_t multiplier = 0; // -100 to 100
		Color tint;

		Type transform_type = Type::None;
	};
}