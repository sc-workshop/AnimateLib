#include "PicText.h"

#include "Animate/XFL/DOM/Text/DOMAbstractText.h"
#include "Animate/XFL/DOM/Text/DOMTextRun.h"
#include "Animate/XFL/DOM/Text/DOMTextAttrs.h"

namespace Animate::Pic
{
	Text::Text()
	{
		m_effect_instance = &m_graphic_effect;
	}

	void Text::WriteXFL(XFL::XFLWriter& writer, uint32_t) const
	{
		DOM::DOMAbstractText text;
		text.type = static_cast<uint8_t>(m_text_type);
		text.bounds = m_text_bound;

		XFL::XFLWriter text_writer(writer, text);

		WriteXFLMatrix(text_writer);
		m_graphic_effect.WriteXFL(text_writer);

		WriteXFLTextRuns(text_writer);
	}

	void Text::WriteXFLTextRuns(XFL::XFLWriter& writer) const
	{
		auto textruns_writer = writer.CreateProperty(DOM::PropTag::TextRuns);

		size_t string_offset = 0;
		for (const auto& style : m_styles)
		{
			DOM::DOMTextRun textrun;
			XFL::XFLWriter textrun_writer(textruns_writer, textrun);

			// Textfield text
			if (!m_characters.empty()) {
				auto character_writer = textrun_writer.CreateProperty(DOM::PropTag::Characters);
				size_t string_end_offset = string_offset + style.length;
				if (!style.length)
				{
					string_end_offset = m_characters.size();
				}

				character_writer.SetValue(m_characters.substr(string_offset, string_offset + style.length));
			}

			// Textfield style
			if (!m_styles.empty()) {
				auto textattrs_writer = textrun_writer.CreateProperty(DOM::PropTag::TextAttrs);
				DOM::DOMTextAttrs text_attrs;
				text_attrs.face = style.fontName;
				text_attrs.fontSize = style.fontSize;

				if (m_text_type == TextType::Dynamic)
				{
					text_attrs.bitmapSize = style.fontSize * 20;
				}

				XFL::XFLWriter(textattrs_writer, text_attrs);
			}

			if (m_text_type == TextType::Dynamic) break;
		}
	}

	void Text::PositionText(Point2D& position)
	{
		m_text_bound.top = position.x;
		m_text_bound.left = position.y;
	}

	void Text::SetWidth(float value)
	{
		m_text_bound.width = value;
	}

	void Text::SetHeight(float value)
	{
		m_text_bound.height = value;
	}

	void Text::ApplyStyle(const TextStyle& reference_style)
	{
		m_styles.clear();
		auto& style = m_styles.emplace_back(reference_style);
		style.length = 0;

	}

}