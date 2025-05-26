#pragma once

#include <string>
#include <array>

#include "XFL/DOM/DOMElement.h"

#include "TypeTraits.h"

namespace Animate::DOM
{
	class DOMLayer : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			Name,
			Color,
			ParentLayerIndex,
			AutoNamed,
			LayerType,
			LayerTextureType,
			AnimationType,
			Visible,
			Locked,
			Outline,
			Current,
			HeightMultiplier,
			HeightLiteral,
			Open,
			PoseLocations,
			IsSelected,
			UseOutlineView,
			Transparent,
			AlphaPercent,
			LayerZDepth,
			AttachedToCamera,
			LayerRiggingIndex,
			Highlighted
		};

		static inline std::array AttributeNames =
		{
			"name",
			"color",
			"parentLayerIndex",
			"autoNamed",
			"layerType",
			"layerTextureType",
			"animationType",
			"visible",
			"locked",
			"outline",
			"current",
			"heightMultiplier",
			"heightLiteral",
			"open",
			"poseLocations",
			"isSelected",
			"useOutlineView",
			"transparent",
			"alphaPercent",
			"layerZDepth",
			"attachedToCamera",
			"layerRiggingIndex",
			"highlighted"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMLayer;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::Name),
				name
			);

			// TODO: rest of props
		}

	public:
		String name;
	};
}