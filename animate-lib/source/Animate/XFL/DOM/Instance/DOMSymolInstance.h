#pragma once

#include <string>
#include <array>

#include "Animate/XFL/DOM/DOMElement.h"
#include "Animate/TypeTraits.h"

namespace Animate::DOM
{
	class DOMSymbolInstance : public DOMElement
	{
	public:
		enum class Attributes : uint32_t
		{
			Name,
			Locked,
			LibraryItemName,
			SymbolType,
			BlendMode,
			CacheAsBitmap,
			Matrix3D,
			RotationX,
			RotationY,
			RotationZ,
			CenterPoint3DX,
			CenterPoint3DY,
			CenterPoint3DZ,
			AccName,
			Description,
			Shortcut,
			TabIndex,
			Silent,
			ForceSimple,
			AutoLabeling,
			HasAccessibleData,
			Loop,
			FirstFrame,
			LastFrame,
			TrackAsMenu,
			IsExtensible,
			AnimationSymbolMode,
			AnimationFrameOffset,
			Selected,
			IsInBackground,
			ReferenceID,
			PrivateDataID,
			UniqueID,
			ExportAsBitmap,
			Bits32,
			IsVisible,
			PuppetHandles,
			PuppetIsBitmap,
			AnimationFrameEndOffset
		};

		static inline std::array AttributeNames =
		{
			"name",
			"locked",
			"libraryItemName",
			"symbolType",
			"blendMode",
			"cacheAsBitmap",
			"matrix3D",
			"rotationX",
			"rotationY",
			"rotationZ",
			"centerPoint3DX",
			"centerPoint3DY",
			"centerPoint3DZ",
			"accName",
			"description",
			"shortcut",
			"tabIndex",
			"silent",
			"forceSimple",
			"autoLabeling",
			"hasAccessibleData",
			"loop",
			"firstFrame",
			"lastFrame",
			"trackAsMenu",
			"isExtensible",
			"animationSymbolMode",
			"animationFrameOffset",
			"selected",
			"isInBackground",
			"referenceID",
			"privateDataID",
			"uniqueID",
			"exportAsBitmap",
			"bits32",
			"isVisible",
			"puppetHandles",
			"puppetIsBitmap",
			"animationFrameEndOffset"
		};

		static const char* GetAtributeName(Attributes attribute)
		{
			return AttributeNames[(uint32_t)attribute];
		}

	public:
		virtual ElementTag GetTag()
		{
			return ElementTag::DOMSymbolInstance;
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