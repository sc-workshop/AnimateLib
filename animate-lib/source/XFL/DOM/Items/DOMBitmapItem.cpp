#include "DOMBitmapItem.h"

namespace Animate::DOM
{
	void DOMBitmapItem::SetAttributes(XFL::XFLWriter& writer)
	{
		DOMMediaItem::SetAttributes(writer);

		writer.WriteAttr(
			DOM::DOMBitmapItem::GetPropName(DOM::DOMBitmapItem::Props::AllowSmoothing),
			smooth
		);

		writer.WriteAttr(
			DOM::DOMBitmapItem::GetPropName(DOM::DOMBitmapItem::Props::CompressionType),
			DOM::DOMBitmapItem::GetCompressionName(compression)
		);

		writer.WriteAttr(
			DOM::DOMBitmapItem::GetPropName(DOM::DOMBitmapItem::Props::UseImportedJPEGData),
			use_jpeg,
			true
		);

		writer.WriteAttr(
			DOM::DOMBitmapItem::GetPropName(DOM::DOMBitmapItem::Props::Quality),
			quality,
			50,
			0,
			100
		);

		writer.WriteAttr(
			DOM::DOMBitmapItem::GetPropName(DOM::DOMBitmapItem::Props::BitmapDataHRef),
			XFL::XFLWriter::MakePrefferedPath(bitmap_href)
		);

		// Frame
		{
			writer.WriteAttr(
				DOM::DOMBitmapItem::GetPropName(DOM::DOMBitmapItem::Props::FrameBottom),
				frame.bottom
			);

			writer.WriteAttr(
				DOM::DOMBitmapItem::GetPropName(DOM::DOMBitmapItem::Props::FrameLeft),
				frame.left
			);

			writer.WriteAttr(
				DOM::DOMBitmapItem::GetPropName(DOM::DOMBitmapItem::Props::FrameRight),
				frame.right
			);

			writer.WriteAttr(
				DOM::DOMBitmapItem::GetPropName(DOM::DOMBitmapItem::Props::FrameTop),
				frame.top
			);
		}
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