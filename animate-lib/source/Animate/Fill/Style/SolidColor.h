#pragma once

#include "Animate/TypeTraits.h"

namespace Animate::Fill
{
	struct SolidFillStyle
	{
		ColorAlpha fill_color;

		bool operator ==(const SolidFillStyle& other) const
		{
			return fill_color == other.fill_color;
		}
	};
}

namespace std {
	template <>
	struct hash<Animate::Fill::SolidFillStyle> {
		size_t operator()(const Animate::Fill::SolidFillStyle& style) const {
			return style.fill_color.as_value();
		}
	};
}