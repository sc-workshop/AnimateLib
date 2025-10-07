#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class DOMAbstractText : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			Name,
			Locked,
			Selected,
			IsInBackground,
			CacheAsBitmap,
			ReferenceID,
			PrivateDataID,
			Top,
			Left,
			Width,
			Height,
			AutoExpand,
			FontRenderingMode,
			AntiAliasSharpness,
			AntiAliasThickness,
			LocalizationStringID,
			Orientation,
			MaxCharacters,
			IsSelectable,
			Scrollable,
			Border,
			VariableName,
			RenderAsHTML,
			LineType,
			AccName,
			Description,
			Shortcut,
			TabIndex,
			Silent,
			ForceSimple,
			AutoLabeling,
			HasAccessibleData,
			IncludeOutlines,
		};

		static inline std::array AttributeNames =
		{
			"name",
			"locked",
			"selected",
			"isInBackground",
			"cacheAsBitmap",
			"referenceID",
			"privateDataID",
			"top",
			"left",
			"width",
			"height",
			"autoExpand",
			"fontRenderingMode",
			"antiAliasSharpness",
			"antiAliasThickness",
			"localizationStringID",
			"orientation",
			"maxCharacters",
			"isSelectable",
			"scrollable",
			"border",
			"variableName",
			"renderAsHTML",
			"lineType",
			"accName",
			"description",
			"shortcut",
			"tabIndex",
			"silent",
			"forceSimple",
			"autoLabeling",
			"hasAccessibleData",
			"includeOutlines",
		};

		static inline std::array TextLineType =
		{
			"single line",
			"multiline",
			"multiline no wrap"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

		static const char* GetTextLineType(uint32_t value)
		{
			return TextLineType[value];
		}

	public:
		virtual ElementTag GetTag()
		{
			switch (type)
			{
			case 0:
				return ElementTag::DOMStaticText;
			
			case 1:
				return ElementTag::DOMDynamicText;

			case 2:
				return ElementTag::DOMInputText;

			default:
				throw wk::Exception("Unknown text type: " + std::to_string(type));
			}
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::Name),
				name
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Top),
				bounds.top
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Left),
				bounds.left
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Width),
				bounds.width
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Height),
				bounds.height
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::LineType),
				GetTextLineType(lineType), GetTextLineType(0)
			);
		}

	public:
		String name;
		int type = 0; // 0 - Static Text,  1 - Dynamic Text, 2 - Input Text
		uint32_t lineType = 0;
		Bound bounds;

	};
}