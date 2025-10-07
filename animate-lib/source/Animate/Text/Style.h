#pragma once

#include "Animate/TypeTraits.h"

namespace Animate
{
	class TextStyle
	{
	public:
		enum class FontStyle {
			Regular = 0,
			Bold,
			Italic
		};

		enum class Aligment {
			Left = 0,
			Center,
			Right,
			Justify
		};

	public:
		size_t length = 0;
		String fontName;
		uint32_t fontSize = 12;
		ColorAlpha fontColor;
		FontStyle fontStyle = FontStyle::Regular;
		Aligment aligment = Aligment::Left;
		bool autoKern = false;
		RangeF margin = {0.f, 0.f };
		float indent = 0.f;
		float lineSpacing = 0.f;
		float lineHeight = 0.f;
		String url;
	};
}