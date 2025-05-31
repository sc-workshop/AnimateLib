#include "PicFrame.h"

#include "Animate/Library/LibraryItem/DocumentPage.h"
#include "Animate/Library/LibraryItem/Media/MediaBits.h"

#include "Animate/Pic/PicBitmap.h"
#include "Animate/Pic/PicSymbol.h"

namespace Animate::Pic
{
	void Frame::WriteXFL(XFL::XFLWriter& root, uint32_t index) const
	{
		DOM::DOMFrame frame;
		frame.duration = m_duration;
		frame.index = index;

		XFL::XFLWriter writer(root, frame);

		auto elements = writer.CreateProperty(DOM::PropTag::Elements);
		for (uint32_t i = 0; ChildrenCount() > i; i++)
		{
			auto& element = ChildAt(i);
			element.WriteXFL(elements, i);
		}
	}

	Symbol& Frame::AddSymbolChildren(Library::DocumentPage& page)
	{
		Symbol& result = AddChild<Symbol>();
		result.SetSymbolPage(page);

		return result;
	}

	Bitmap& Frame::AddBitmapChildren(Library::MediaBits& bits)
	{
		Bitmap& bitmap = AddChild<Bitmap>();
		bitmap.SetBits(bits);
		return bitmap;
	}

}
