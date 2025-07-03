#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class FillStyle : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			Index
		};

		static inline std::array AttributeNames =
		{
			"index"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::FillStyle;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::Index),
				index
			);
		}

	public:
		uint32_t index;
	};
}