#pragma once

#include <string>
#include <array>

#include "Animate/Pic/PicLayer.h"
#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

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

		static inline std::array LayerTypeNames =
		{
			"normal",
			"folder",
			"mask",
			"guide",
			"camera"
		};

		static const char* GetLayerTypeName(Pic::Layer::Type attribute)
		{
			return LayerTypeNames[(uint32_t)attribute];
		}

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

			writer.WriteAttr(
				GetAtributeName(Attributes::LayerType),
				GetLayerTypeName(type),
				GetLayerTypeName(Pic::Layer::Type::Normal)
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Locked),
				locked, false
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::ParentLayerIndex),
				parentIndex, std::numeric_limits<size_t>::max()
			);

			// TODO: rest of props
		}

	public:
		String name;
		Pic::Layer::Type type;
		bool locked = false;
		size_t parentIndex = std::numeric_limits<size_t>::max();
	};
}