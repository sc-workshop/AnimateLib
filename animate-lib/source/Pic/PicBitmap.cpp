#include "PicBitmap.h"

#include "Library/LibraryItem/Media/MediaBits.h"

namespace Animate::Pic
{
	void Bitmap::WriteXFL(XFL::XFLWriter& root, uint32_t) const
	{
		if (!m_mediBits) return;

		DOM::DOMBitmapInstance instance;
		instance.libraryItemName = XFL::XFLWriter::MakePrefferedPath(m_mediBits->GetItemPath());

		XFL::XFLWriter writer(root, instance);
	}

	Library::MediaBits& Bitmap::GetBits() const
	{
		assert(m_mediBits == nullptr);
		return *m_mediBits;
	}

	void Bitmap::SetBits(Library::MediaBits& bits)
	{
		m_mediBits = &bits;
	}
}

