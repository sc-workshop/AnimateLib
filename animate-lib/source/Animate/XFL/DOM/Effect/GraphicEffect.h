#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"
#include "Animate/Effects/GraphicEffect.h"

namespace Animate::DOM
{
	class GraphicEffect : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			BlurX,
			BlurY,
			Quality,
			Angle,
			Distance,
			HighlightAlpha,
			HighlightColor,
			Knockout,
			ShadowAlpha,
			ShadowColor,
			Strength,
			Type,
			Ratio,
			Alpha,
			Color,
			Inner,
			HideObject,
			Ratios,
			Alphas,
			Colors,
			IsEnabled
		};

		static inline std::array AttributeNames =
		{
			"blurX",
			"blurY",
			"quality",
			"angle",
			"distance",
			"highlightAlpha",
			"highlightColor",
			"knockout",
			"shadowAlpha",
			"shadowColor",
			"strength",
			"type",
			"ratio",
			"alpha",
			"color",
			"inner",
			"hideObject",
			"ratios",
			"alphas",
			"colors",
			"isEnabled"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			switch (type) {
			case Effect::GraphicEffect::Type::AdjustColor:
				return ElementTag::AdjustColorFilter;
			case Effect::GraphicEffect::Type::Bevel:
				return ElementTag::BevelFilter;
			case Effect::GraphicEffect::Type::Blur:
				return ElementTag::BlurFilter;
			case Effect::GraphicEffect::Type::DropShadow:
				return ElementTag::DropShadowFilter;
			case Effect::GraphicEffect::Type::Glow:
				return ElementTag::GlowFilter;
			case Effect::GraphicEffect::Type::GradientBevel:
				return ElementTag::GradientBevelFilter;
			case Effect::GraphicEffect::Type::GradientFlow:
				return ElementTag::GradientGlowFilter;
			default:
				throw wk::Exception("Not implemented");
			}
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr<uint32_t>(
				GetAtributeName(Attributes::BlurX), blurX, 4
			);

			writer.WriteAttr<uint32_t>(
				GetAtributeName(Attributes::BlurY), blurY, 4
			);

			writer.WriteAttr<uint32_t>(
				GetAtributeName(Attributes::Quality), quality, 1
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::IsEnabled), isEnabled, true
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Color), color, false
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Alpha), (float)color.a / 0xFF, 1.0f
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Strength), strength, 1.f, 0.f, 255.f
			);
		}

	public:
		Effect::GraphicEffect::Type type;

		bool isEnabled = true;
		uint8_t blurX = 4;
		uint8_t blurY = 4;
		uint32_t quality = 1;
		ColorAlpha color;
		float strength = 1.f;
	};
}