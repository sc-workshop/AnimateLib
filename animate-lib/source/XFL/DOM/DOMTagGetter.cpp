#include "DOMElements.h"
#include "DOMProps.h"
#include "Items/DOMBitmapItem.h"

namespace Animate::DOM
{
	const char* GetPropName(PropTag tag)
	{
		return PropTagNames[(uint32_t)tag];
	}

	const char* GetElementTag(ElementTag tag)
	{
		return ElementTagNames[(uint32_t)tag];
	}

	const char* DOMBitmapItem::GetCompressionName(uint32_t index)
	{
		return DOMBitmapItem::CompressionName[index];
	}

	const char* DOMBitmapItem::GetPropName(DOMBitmapItem::Props prop)
	{
		return DOMBitmapItem::PropNames[(uint32_t)prop];
	}
}