#pragma once

#include "PicObject.h"

namespace Animate::Library
{
	class DocumentPage;
}

namespace Animate::Pic
{
	class Symbol : public Object
	{
	public:
		Symbol();

	public:
		enum class InstanceType
		{
			Button = 0,
			Graphic,
			MovieClip,
			IkContainer,
			Puppet,
			PuppetBase,
			Media3D
		};

	public:
		virtual bool IsPicSymbol() const override { return true; };
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t index) const override;

	public:
		String GetName() const { return m_name; }
		void SetName(const String& name) { m_name = name; }
		virtual void SetPIInstanceName(const String& name) override { SetName(name); }

		InstanceType GetSymbolBehavior() const { return m_type; }
		void SetSymbolBehavior(InstanceType type) { m_type = type; }

		void SetSymbolPage(Library::DocumentPage& page) { m_page = &page; }
		Library::DocumentPage& GetSymbolPage() const {
			assert(m_page != nullptr);
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
		virtual Object* CloneObject() const override
		{
			return new Symbol(*this);
		}

	private:
		Library::DocumentPage* m_page = nullptr;
		Matrix m_matrix;
		Library::GraphicEffectInstance m_graphic_effect;

		// Should be in PropertyInstance but uh ok
		String m_name;
		InstanceType m_type = InstanceType::MovieClip;
	};
}