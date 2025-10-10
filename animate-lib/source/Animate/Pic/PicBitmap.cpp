#include "PicBitmap.h"

#include "Animate/Library/LibraryItem/Media/MediaBits.h"
#include "Animate/Document/SketchDocument.h"

namespace Animate::Pic
{
	void Bitmap::WriteXFL(XFL::XFLWriter& root, uint32_t) const
	{
		if (!m_mediaBits) return;

		auto& doc = OwnerDoc();
		doc.AddSymbolReferenceToSymDependCache(*m_mediaBits);

		DOM::DOMBitmapInstance instance;
		instance.libraryItemName = XFL::XFLWriter::MakePrefferedPath(m_mediaBits->GetItemPath());

		XFL::XFLWriter writer(root, instance);
		WriteXFLMatrix(writer);
	}

	Library::MediaBits& Bitmap::GetBits() const
	{
		assert(m_mediaBits == nullptr);
		return *m_mediaBits;
	}

	void Bitmap::SetBits(Library::MediaBits& bits)
	{
		m_mediaBits = &bits;
	}
}

