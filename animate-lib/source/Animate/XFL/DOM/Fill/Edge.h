#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class Edge : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			FillStyle0,
			FillStyle1,
			StrokeStyle,
			Edges,
			Cubics,
		};

		static inline std::array AttributeNames =
		{
			"fillStyle0",
			"fillStyle1",
			"strokeStyle",
			"edges",
			"cubics",
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::Edge;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr<uint32_t>(
				GetAtributeName(Attributes::FillStyle0),
				fill_style_0, 0
			);

			writer.WriteAttr<uint32_t>(
				GetAtributeName(Attributes::FillStyle1),
				fill_style_1, 0
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Edges),
				edges
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::Cubics),
				cubics
			);
		}

	public:
		uint32_t fill_style_0 = 0;
		uint32_t fill_style_1 = 0;
		std::string edges = "";
		std::string cubics = "";

	};
}