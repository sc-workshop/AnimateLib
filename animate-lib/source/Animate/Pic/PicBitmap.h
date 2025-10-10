#pragma once

#include "PicObject.h"

#include "Animate/XFL/DOM/Instance/DOMBitmapInstance.h"

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

		virtual bool GetMatrix(Matrix& matrix) const override  { 
			matrix = m_matrix;
			return true;
		}
		virtual bool SetMatrix(const Matrix& matrix) override { 
			m_matrix = matrix; 
			return true;
		}

	protected:
		virtual Object* CloneObject() override
		{
			return new Bitmap(*this);
		}

	private:
		Library::MediaBits* m_mediaBits;
		Matrix m_matrix;
	};
}