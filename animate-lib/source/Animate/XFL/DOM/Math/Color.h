#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class Color : public DOMElement
	{
	public:
		static inline float DefaultMultiplier = 1.0f;
		static inline float MinMultiplier = 0.0f;
		static inline float MaxMulitplier = 1.0f;

		static inline int16_t DefaultOffset = 0;
		static inline int16_t MinOffset = -255;
		static inline int16_t MaxOffset = 255;
	public:
		Color()
		{
		}

	public:
		enum class Attributes : uint32_t
		{
			TintColor,
			Brightness,
			TintMultiplier,
			AlphaMultiplier,
			RedMultiplier,
			BlueMultiplier,
			GreenMultiplier,
			AlphaOffset,
			RedOffset,
			BlueOffset,
			GreenOffset,
		};

		static inline std::array AttributeNames =
		{
			"tintColor",
			"brightness",
			"tintMultiplier",
			"alphaMultiplier",
			"redMultiplier",
			"blueMultiplier",
			"greenMultiplier",
			"alphaOffset",
			"redOffset",
			"blueOffset",
			"greenOffset",
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::Color;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			// Multiply
			{
				writer.WriteAttr(
					GetAtributeName(Attributes::AlphaMultiplier),
					alpha_multiplier,
					DefaultMultiplier,
					MinMultiplier,
					MaxMulitplier
				);

				writer.WriteAttr(
					GetAtributeName(Attributes::RedMultiplier),
					red_multiplier,
					DefaultMultiplier,
					MinMultiplier,
					MaxMulitplier
				);

				writer.WriteAttr(
					GetAtributeName(Attributes::GreenMultiplier),
					green_multiplier,
					DefaultMultiplier,
					MinMultiplier,
					MaxMulitplier
				);

				writer.WriteAttr(
					GetAtributeName(Attributes::BlueMultiplier),
					blue_multiplier,
					DefaultMultiplier,
					MinMultiplier,
					MaxMulitplier
				);
			}

			// Offset
			{
				writer.WriteAttr(
					GetAtributeName(Attributes::AlphaOffset),
					alpha_offset,
					DefaultOffset,
					MinOffset,
					MaxOffset
				);

				writer.WriteAttr(
					GetAtributeName(Attributes::RedOffset),
					red_offset,
					DefaultOffset,
					MinOffset,
					MaxOffset
				);

				writer.WriteAttr(
					GetAtributeName(Attributes::GreenOffset),
					green_offset,
					DefaultOffset,
					MinOffset,
					MaxOffset
				);

				writer.WriteAttr(
					GetAtributeName(Attributes::BlueOffset),
					blue_offset,
					DefaultOffset,
					MinOffset,
					MaxOffset
				);
			}
		}

	public:
		float alpha_multiplier = 1.0f;
		float red_multiplier = 1.0f;
		float green_multiplier = 1.0f;
		float blue_multiplier = 1.0f;

		int16_t alpha_offset = 0;
		int16_t red_offset = 0;
		int16_t green_offset = 0;
		int16_t blue_offset = 0;
	};
}