#pragma once

#include <string>
#include <array>

#include "XFL/DOM/Items/DOMItem.h"

namespace Animate::DOM
{
	class DOMFolderItem : public DOMItem
	{
	public:
		DOMFolderItem() : DOMItem(DOMItem::Type::Folder)
		{
		}
	public:
		enum class Attributes : uint32_t
		{
			IsExpanded
		};

		static inline std::array AttributeNames =
		{
			"isExpanded"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		void SetAttributes(XFL::XFLWriter& writer)
		{
			DOMItem::SetAttributes(writer);

			writer.WriteAttr(
				GetAtributeName(Attributes::IsExpanded),
				is_expanded
			);
		}

	public:
		bool is_expanded;
	};
}