#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class Shape : public DOMElement
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
			IsDrawingObject,
			IsFloating,
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
			"isDrawingObject",
			"isFloating",
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMShape;
		}

		void SetAttributes(XFL::XFLWriter& writer) {
			writer.WriteAttr(
				GetAtributeName(Attributes::IsDrawingObject),
				isDrawing, false
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::IsFloating),
				isFloater, false
			);
		
		}

	public:
		bool isDrawing = false;
		bool isFloater = false;
	};
}