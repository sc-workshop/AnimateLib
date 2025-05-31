#pragma once
#pragma once

#include "PicObject.h"

#include "Animate/XFL/DOM/Instance/DOMBitmapInstance.h"

namespace Animate::Library
{
	class DocumentPage;
}

namespace Animate::Pic
{
	class Symbol : public Object
	{
	public:
		using Object::Object;

	public:
		virtual bool IsPicSymbol() const override { return true; };
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t index) const override;

	public:
		void SetSymbolPage(Library::DocumentPage& page) { m_page = &page; }
		Library::DocumentPage& GetSymbolPage() {
			assert(m_page == nullptr);
			return *m_page;
		}

		virtual bool GetMatrix(Matrix& matrix) const override {
			matrix = m_matrix;
			return true;
		}

		virtual bool SetMatrix(const Matrix& matrix) override {
			m_matrix = matrix;
			return true;
		}

	protected:
		virtual Object* CloneObject()
		{
			return new Symbol(*this);
		}

	private:
		Library::DocumentPage* m_page = nullptr;
		Matrix m_matrix;
	};
}