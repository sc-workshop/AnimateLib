#pragma once

#include "XFL/IoFile.h"

namespace Animate
{
	class MediaAsset
	{
	public:
		enum class Type
		{
			Unknown = 0,
			Video,
			Audio,
			Bitmap
		};

	public:
		virtual Type GetMediaType() const = 0;
		virtual void WriteXFLContent(XFL::XflIoFile& file) const = 0;
	};
}