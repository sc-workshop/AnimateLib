#pragma once

#include <array>
#include <string>

#include "core/generic/static.h"

namespace Animate::DOM
{
	class DOMBitmapItem
	{
		WK_STATIC_CLASS(DOMBitmapItem);

	public:
		static const inline std::array CompressionName
		{
			"",
			"photo",
			"lossless"
		};

		static const char* GetCompressionName(uint32_t);

		static const inline std::array PropNames
		{
			"allowSmoothing",
			"useDeblocking",
			"quality",
			"useImportedJPEGData",
			"compressionType",
			"originalCompressionType",
			"href",
			"bitmapDataHRef",
			"frameLeft",
			"frameTop",
			"frameRight",
			"frameBottom",
			"isJPEG",
			"maxScaleUsed"
		};

		enum class Props : uint32_t
		{
			AllowSmoothing,
			UseDeblocking,
			Quality,
			UseImportedJPEGData,
			CompressionType,
			OriginalCompressionType,
			Href,
			BitmapDataHRef,
			FrameLeft,
			FrameTop,
			FrameRight,
			FrameBottom,
			IsJPEG,
			MaxScaleUsed
		};

		static const char* GetPropName(Props);
	};
}