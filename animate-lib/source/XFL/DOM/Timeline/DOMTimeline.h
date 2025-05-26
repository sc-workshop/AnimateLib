#pragma once

#include <string>
#include <array>

#include "XFL/DOM/DOMElement.h"

#include <core/math/color_rgb.h>

namespace Animate::DOM
{
	class DOMTimeline : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			Name,
			CurrentFrame,
			Guides,
			HrefDataBindingsFile,
			CameraLayerEnabled,
			LayerDepthEnabled,
			TexturePublishingEnabled,
		};

		static inline std::array AttributeNames =
		{
			"name",
			"currentFrame",
			"guides",
			"hrefDataBindingsFile",
			"cameraLayerEnabled",
			"layerDepthEnabled",
			"texturePublishingEnabled",
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMTimeline;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::Name),
				name
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::CurrentFrame),
				current_frame
			);
		}

	public:
		std::u16string name;
		size_t current_frame = 0;
	};
}