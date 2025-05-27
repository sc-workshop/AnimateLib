#pragma once

#include <array>
#include <string>

#include "Animate/XFL/DOM/Items/DOMMediaItem.h"

namespace Animate::DOM
{
	class DOMBitmapItem : public DOMMediaItem
	{
	public:
		DOMBitmapItem() : DOMMediaItem(DOMMediaItem::Type::Bitmap)
		{ }

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

		virtual void SetAttributes(XFL::XFLWriter& writer);

	public:
		bool smooth = false;
		uint32_t compression = 0;
		bool use_jpeg = false;
		int quality = 0;
		Path bitmap_href;
		wk::Rect frame;
	};
}