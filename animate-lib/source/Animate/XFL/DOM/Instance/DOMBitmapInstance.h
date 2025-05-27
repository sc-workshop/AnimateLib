#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class DOMBitmapInstance : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			LibraryItemName
		};

		static inline std::array AttributeNames =
		{
			"libraryItemName",
			//"name"
			//"locked"
			//"selected"
			//"isInBackground"
			//"cacheAsBitmap"
			//"referenceID"
			//"privateDataID"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMBitmapInstance;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::LibraryItemName),
				libraryItemName
			);
		}

	public:
		std::u16string libraryItemName;
	};
}