#pragma once

#include "Animate/XFL/DOM/Items/DOMItem.h"

namespace Animate::DOM
{
	class DOMMediaItem : public DOMItem
	{
	public:
		enum class Type
		{
			Bitmap
		};

	public:
		DOMMediaItem(Type type);

	public:
		virtual void SetAttributes(XFL::XFLWriter& writer);

	public:
		time_t source_last_imported = 0;
		size_t external_file_crc32 = 0;
		size_t external_file_size = 0;
	};
}