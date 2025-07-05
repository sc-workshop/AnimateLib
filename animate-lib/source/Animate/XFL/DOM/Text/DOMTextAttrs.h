#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class DOMTextAttrs : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			AliasText,
			Alignment,
			AutoKern,
			Bold,
			CharacterPosition,
			Face,
			WebFontInfo,
			FillColor,
			Alpha,
			Indent,
			Italic,
			LeftMargin,
			LetterSpacing,
			LineSpacing,
			LineHeight,
			RightMargin,
			Size,
			BitmapSize,
			Target,
			Url,
			Rotation,
		};

		static inline std::array AttributeNames =
		{
			"aliasText",
			"alignment",
			"autoKern",
			"bold",
			"characterPosition",
			"face",
			"webFontInfo",
			"fillColor",
			"alpha",
			"indent",
			"italic",
			"leftMargin",
			"letterSpacing",
			"lineSpacing",
			"lineHeight",
			"rightMargin",
			"size",
			"bitmapSize",
			"target",
			"url",
			"rotation",
		};

		static inline std::array TextAligment =
		{
			"start",
			"end",
			"left",
			"center",
			"right",
			"justify",
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

		static const char* GetTextAligmentName(uint32_t value)
		{
			return TextAligment[(uint32_t)value];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMTextAttrs;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::AliasText),
				aliasText, false
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Alignment),
				GetTextAligmentName(aligment), GetTextAligmentName(0u)
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::AutoKern),
				autoKern, false
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Bold),
				bold, false
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Italic),
				italic, false
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Rotation),
				rotation, false
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Face),
				face
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::FillColor),
				color, false
			);

			writer.WriteAttr<float>(
				GetAtributeName(Attributes::Alpha),
				(float)color.a / 0xFF, 0.f
			);

			writer.WriteAttr<float>(
				GetAtributeName(Attributes::Indent),
				indent, 0.f
			);

			writer.WriteAttr<float>(
				GetAtributeName(Attributes::LineSpacing),
				lineSpacing, 0.f
			);

			writer.WriteAttr<float>(
				GetAtributeName(Attributes::LineHeight),
				lineHeight, 0.f
			);

			writer.WriteAttr<float>(
				GetAtributeName(Attributes::LeftMargin),
				margin.x, 0.f
			);

			writer.WriteAttr<float>(
				GetAtributeName(Attributes::RightMargin),
				margin.y, 0.f
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Size),
				fontSize, 0u
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::BitmapSize),
				bitmapSize, 0u
			);
		}

	public:
		bool aliasText = false;
		uint32_t aligment = 0; // 0: start, 1: end, 2: left, 3: center, 4: right, 5: justify
		bool autoKern = false;
		bool bold = false;
		bool italic = false;
		bool rotation = false;
		String face;
		ColorAlpha color;

		float indent = 0.f;
		float lineSpacing = 0.f;
		float lineHeight = 0.f;

		RangeF margin;

		uint32_t fontSize = 0;
		uint32_t bitmapSize = 0;
	};
}