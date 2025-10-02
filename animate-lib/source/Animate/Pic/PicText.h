#pragma once

#include "PicObject.h"

#include "Animate/Text/Style.h"

namespace Animate::Pic
{
	class Text : public Object
	{
	public:
		enum class TextType : uint8_t
		{
			Static = 0,
			Dynamic,
			Input
		};

	public:
		Text();

	public:
		virtual bool IsPicText() const override { return true; };
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t) const override;
		void WriteXFLTextRuns(XFL::XFLWriter& writer) const;

	public:
		void PositionText(Point2D& position);

		TextType GetTextType() const { return m_text_type; }
		void SetTextType(TextType type) { m_text_type = type; }

		virtual void SetPIInstanceName(const String& name) {
			m_name = name;
		};

		virtual bool GetMatrix(Matrix& matrix) const override {
			matrix = m_matrix;
			return true;
		}

		virtual bool SetMatrix(const Matrix& matrix) override {
			m_matrix = matrix;
			return true;
		}

		virtual void SetWidth(float value) override;
		virtual void SetHeight(float value) override;

		void ApplyStyle(const TextStyle& style);
			
	protected:
		virtual Object* CloneObject() override
		{
			return new Text(*this);
		}

	private:
		Bound m_text_bound;
		TextType m_text_type = TextType::Static;
		List<TextStyle> m_styles;
		String m_characters;
		String m_name;

		Matrix m_matrix;
		Library::GraphicEffectInstance m_graphic_effect;
	};
}