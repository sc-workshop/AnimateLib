#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class BitmapFill : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			BitmapPath,
			IsClipped
		};

		static inline std::array AttributeNames =
		{
			"bitmapPath",
			"bitmapIsClipped"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::BitmapFill;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::BitmapPath), XFL::XFLWriter::MakePrefferedPath(bitmap)
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::IsClipped), isClipped, false
			);
		}

	public:
		Path bitmap;
		bool isClipped = false;
	};
}