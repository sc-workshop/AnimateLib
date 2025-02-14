#pragma once

#include <string>
#include <array>

#include "XFL/DOM/Items/DOMItem.h"

namespace Animate::DOM
{
	class DOMSymbolItem : public DOMItem
	{
	public:
		DOMSymbolItem() : DOMItem(DOMItem::Type::Symbol)
		{ }
	public:
		static const inline std::array SymbolType
		{
			"graphic",
			"movie clip",
			"button",
			"ik container",
			"puppet",
			"puppetBase",
			"media 3D"
		};
		
		enum class Attributes : uint32_t
		{
			SymbolType,
			ScaleGridLeft,
			ScaleGridTop,
			ScaleGridRight,
			ScaleGridBottom,
			LastModified,
			HasValidCenterPoint,
			LastUniqueIdentifier,
			IsFlexComponent,
			IsSpriteSubclass,
			TransformCenterPoint,
			DisplayAsComponent,
			Tooltip,
			CustomIconID,
			DescriptionType,
			ActionscriptClass,
			SwfScmHRef,
			SwfScmSourceFilename,
			LivePreviewScmHRef,
			LivePreviewScmSourceFilename,
			PersistLivePreview11,
			LivePreview11ScmHRef,
			LivePreview11ScmSourceFilename,
			CustomUIScmHRef,
			CustomUIScmSourceFilename,
			SymbolDescription,
			EditFrameIndex,
			RequiredMinimumPlayerVersionName,
			RequiredMinimumPlayerVersion,
			RequiredMinimumASVersion,
			ParametersAreLocked,
			ParametersAreNew,
			SourceItemID,
		};

		static inline std::array AttributeNames =
		{
			"symbolType",
			"scaleGridLeft",
			"scaleGridTop",
			"scaleGridRight",
			"scaleGridBottom",
			"lastModified",
			"hasValidCenterPoint",
			"lastUniqueIdentifier",
			"isFlexComponent",
			"isSpriteSubclass",
			"transformCenterPoint",
			"displayAsComponent",
			"tooltip",
			"customIconID",
			"descriptionType",
			"actionscriptClass",
			"swfScmHRef",
			"swfScmSourceFilename",
			"livePreviewScmHRef",
			"livePreviewScmSourceFilename",
			"persistLivePreview11",
			"livePreview11ScmHRef",
			"livePreview11ScmSourceFilename",
			"customUIScmHRef",
			"customUIScmSourceFilename",
			"symbolDescription",
			"editFrameIndex",
			"requiredMinimumPlayerVersionName",
			"requiredMinimumPlayerVersion",
			"requiredMinimumASVersion",
			"parametersAreLocked",
			"parametersAreNew",
			"sourceItemID",
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

		static const char* GetSymbolTypeName(size_t index)
		{
			return SymbolType[index];
		}

	public:
		void SetAttributes(XFL::XFLWriter& writer)
		{
			DOMItem::SetAttributes(writer);

			writer.WriteAttr(
				GetAtributeName(Attributes::SymbolType),
				GetSymbolTypeName(symbol_type)
			);

			writer.WriteAttr(
				GetAtributeName(Attributes::LastModified),
				last_modified
			);
		}

	public:
		size_t symbol_type;
		time_t last_modified;
	};
}