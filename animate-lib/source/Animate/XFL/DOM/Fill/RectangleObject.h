#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class RectangleObject : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			ObjectWidth,
			ObjectHeight,
			X,
			Y,
			Name,
			Locked,
			LockFlag,
			TopLeftRadius,
			TopRightRadius,
			BottomLeftRadius,
			BottomRightRadius,
			Selected,
			IsInBackground,
			CacheAsBitmap,
			ReferenceID,
			PrivateDataID,
		};

		static inline std::array AttributeNames =
		{
			"objectWidth",
			"objectHeight",
			"x",
			"y",
			"name",
			"locked",
			"lockFlag",
			"topLeftRadius",
			"topRightRadius",
			"bottomLeftRadius",
			"bottomRightRadius",
			"selected",
			"isInBackground",
			"cacheAsBitmap",
			"referenceID",
			"privateDataID",
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMRectangleObject;
		}

		void SetAttributes(XFL::XFLWriter& writer) 
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::ObjectWidth),
				rectangle.width, 0.f
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::ObjectHeight),
				rectangle.height, 0.f
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::X),
				rectangle.x, 0.f
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Y),
				rectangle.y, 0.f
			);
		}

	public:
		Bound rectangle;
	};
}