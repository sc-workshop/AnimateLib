#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class SolidColor : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			Color,
			Alpha
		};

		static inline std::array AttributeNames =
		{
			"color",
			"alpha"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::SolidColor;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::Color),
				color, false, {0, 0, 0, 0}
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Alpha),
				(float)color.a / 0xFF, 1.0f
			);
		}

	public:
		ColorAlpha color;
	};
}