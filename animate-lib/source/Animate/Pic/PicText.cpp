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
		text.name = m_name;
		text.type = static_cast<uint8_t>(m_text_type);
		text.bounds = m_text_bound;
		text.lineType = (uint32_t)GetLineType();

		XFL::XFLWriter text_writer(writer, text);

		WriteXFLMatrix(text_writer);
		if (m_graphic_effect.GetColorTransformMode() != ColorTransform::Type::None)
		{
			XFL::XFLProp color = text_writer.CreateProperty(DOM::PropTag::Color);
			m_graphic_effect.WriteXFLColor(color);
		}

		WriteXFLTextRuns(text_writer);

		auto effects = m_graphic_effect.GetGraphicEffectList();
		if (!effects.empty()) {
			auto effect_writer = text_writer.CreateProperty(DOM::PropTag::Filters);

			for (auto effect : effects) {
				WriteXFLGraphicEffect(effect_writer, *effect);
			}
		}
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
				/*size_t string_end_offset = string_offset + style.length;
				if (!style.length)
				{
					string_end_offset = m_characters.size();
				}*/

				character_writer.SetValue(m_characters.substr(string_offset, string_offset + style.length));
			}

			// Textfield style
			if (!m_styles.empty()) {
				auto textattrs_writer = textrun_writer.CreateProperty(DOM::PropTag::TextAttrs);
				DOM::DOMTextAttrs text_attrs;
				text_attrs.face = style.fontName;
				text_attrs.fontSize = style.fontSize;
				text_attrs.autoKern = style.autoKern;
				text_attrs.color = style.fontColor;
				text_attrs.margin = style.margin;
				text_attrs.indent = style.indent;
				text_attrs.lineSpacing = style.lineSpacing;
				text_attrs.lineHeight = style.lineHeight;
				text_attrs.url = style.url;
				text_attrs.aligment = (uint32_t)style.aligment;

				switch (style.fontStyle) {
				case TextStyle::FontStyle::Italic:
					text_attrs.italic = true;
					break;
				case TextStyle::FontStyle::Bold:
					text_attrs.bold = true;
					break;
				default:
					break;
				}

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