#include "PicShape.h"

#include "Animate/XFL/DOM/Fill/Shape.h"
#include "Animate/XFL/DOM/Fill/Edge.h"
#include "Animate/XFL/DOM/Fill/FillStyle.h"
#include "Animate/XFL/DOM/Fill/Style/SolidColor.h"

namespace Animate::Pic
{
	void Shape::CreateEdge(const FillStyle& style, const std::string& contour, bool is_hole, bool merge_edges)
	{
		size_t style_index = 0;

		if (merge_edges)
		{
			auto style_it = std::find(m_fill_styles.begin(), m_fill_styles.end(), style);

			if (style_it != m_fill_styles.end())
			{
				style_index = std::distance(m_fill_styles.begin(), style_it) + 1;
			}
			else
			{
				m_fill_styles.push_back(style);
				style_index = m_fill_styles.size();
			}
		}
		else
		{
			m_fill_styles.push_back(style);
			style_index = m_fill_styles.size();
		}

		auto& edge = m_edges.emplace_back();
		edge.contour = contour;
		edge.style = (uint32_t)style_index;
		edge.is_hole = is_hole;
	}

	void Shape::WriteXFL(XFL::XFLWriter& writer, uint32_t) const
	{
		DOM::Shape shape;
		XFL::XFLWriter shape_writer(writer, shape);

		WriteXFLMatrix(shape_writer);
		WriteXFLStyles(shape_writer);
		WriteXFLEdges(shape_writer);
	}

	void Shape::WriteXFLStyles(XFL::XFLWriter& writer) const
	{
		auto fills = writer.CreateProperty(DOM::PropTag::Fills);

		uint32_t style_index = 1;
		for (auto& style : m_fill_styles)
		{
			WriteXFLStyle(fills, style, style_index);
			style_index++;
		}
	}

	void Shape::WriteXFLStyle(XFL::XFLWriter& writer, const FillStyle& style, uint32_t index) const
	{
		DOM::FillStyle fill_style;
		fill_style.index = index;

		XFL::XFLWriter root(writer, fill_style);
		std::visit([&root](const auto& fill_style) {
			using T = std::decay_t<decltype(fill_style)>;

			if constexpr (std::is_same_v<T, Fill::SolidFillStyle>)
			{
				DOM::SolidColor style;
				style.color = fill_style.fill_color;

				XFL::XFLWriter style_writer(root, style);
			}
			else if constexpr (std::is_same_v<T, Fill::BitmapFillStyle>)
			{
				// TODO: implement
			}
			}, style);
	}

	void Shape::WriteXFLEdges(XFL::XFLWriter & writer) const
	{
		auto edges = writer.CreateProperty(DOM::PropTag::Edges);

		for (auto& edge : m_edges)
		{
			DOM::Edge edge_prop;
			if (edge.is_hole)
			{
				edge_prop.fill_style_0 = edge.style;
			}
			else
			{
				edge_prop.fill_style_1 = edge.style;
			}
			
			edge_prop.edges = edge.contour;
			XFL::XFLWriter(edges, edge_prop);
		}
	}
}