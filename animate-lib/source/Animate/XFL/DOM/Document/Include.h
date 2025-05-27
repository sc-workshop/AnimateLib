#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"

namespace Animate::DOM
{
	class Include : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			Href,
			ItemIcon,
			LoadImmediate,
			ItemID,
			LastModified,
			IsLinked,
			IsCCLibAssetParent
		};

		static inline std::array AttributeNames =
		{
			"href",
			"itemIcon",
			"loadImmediate",
			"itemID",
			"lastModified",
			"isLinked",
			"isCCLibAssetParent"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::Include;
		}

		void SetAttributes(XFL::XFLWriter& writer)
		{
			writer.WriteAttr(
				GetAtributeName(Attributes::Href),
				XFL::XFLWriter::MakePrefferedPath(href, true)
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::ItemIcon),
				item_icon,
				std::numeric_limits<int>::max()
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::LoadImmediate),
				load_immediate,
				true
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::ItemID),
				item_id
			);

			writer.WriteAttr<uint32_t>(
				GetAtributeName(Attributes::LastModified),
				(uint32_t)last_modified,
				0
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::IsLinked),
				is_linked,
				false
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::IsCCLibAssetParent),
				is_cc_lib_asset_parent,
				false
			);
		}

	public:
		Path href;
		int item_icon = 0;
		bool load_immediate = false;
		String item_id;
		time_t last_modified = 0;
		bool is_linked = false;
		bool is_cc_lib_asset_parent = false;
	};
}