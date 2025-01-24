#pragma once

#include <array>
#include <string>

#include "DOMElement.h"

namespace Animate::DOM
{
	class DOMItem : public DOMElement
	{
	public:
		enum class Type
		{
			Folder,
			Bitmap
		};

		enum class Props
		{
			Name,
			LinkageExportForAS,
			LinkageExportForRS,
			LinkageImportForRS,
			LinkageExportInFirstFrame,
			LinkageIdentifier,
			LinkageBaseClass,
			LinkageClassName,
			LinkageURL,
			SourceFlashFilepath,
			SourceLibraryItemHRef,
			SourceLastModified,
			SourceAutoUpdate,
			ItemID,
			PrivateDataID
		};

		static const inline std::array PropNames =
		{
			"name",
			"linkageExportForAS",
			"linkageExportForRS",
			"linkageImportForRS",
			"linkageExportInFirstFrame",
			"linkageIdentifier",
			"linkageBaseClass",
			"linkageClassName",
			"linkageURL",
			"sourceFlashFilepath",
			"sourceLibraryItemHRef",
			"sourceLastModified",
			"sourceAutoUpdate",
			"itemID",
			"privateDataID"
		};

		static const char* GetPropName(Props prop)
		{
			return PropNames[(uint32_t)prop];
		}

	public:
		static const inline std::u16string Default_Name = u"";
		static const inline std::string Default_ItemID = "";

	public:
		DOMItem(Type type)
		{ 
			switch (type)
			{
			case Type::Folder:
				m_tag = ElementTag::DOMFolderItem;
				break;
			case Type::Bitmap:
				m_tag = ElementTag::DOMBitmapItem;
				break;
			default:
				throw wk::Exception();
			}
		}

	public:
		virtual ElementTag GetTag() { return m_tag; };
		virtual void SetAttributes(XFL::XFLWriter& writer);

	public:
		std::u16string name;
		std::string itemId;

	private:
		ElementTag m_tag;
	};
}