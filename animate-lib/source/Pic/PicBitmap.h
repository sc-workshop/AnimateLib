#pragma once

#include "PicObject.h"

#include "XFL/DOM/Instance/DOMBitmapInstance.h"

namespace Animate::Library
{
	class MediaBits;
}

namespace Animate::Pic
{
	class Bitmap : public Object
	{
	public:
		using Object::Object;

	public:
		virtual bool IsPicBitmap() const override { return true; };
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t index) const override;

	public:
		Library::MediaBits& GetBits() const;
		void SetBits(Library::MediaBits& bits);

	private:
		Library::MediaBits* m_mediBits;
	};
}