#include "PicShape.h"

#include "Animate/XFL/DOM/Fill/Shape.h"
#include "Animate/XFL/DOM/Fill/Edge.h"
#include "Animate/XFL/DOM/Fill/FillStyle.h"
#include "Animate/XFL/DOM/Fill/Style/SolidColor.h"

namespace Animate::Pic
{
	void Shape::CreateEdge(const FillStyle& style, const std::string& edge)
	{
		auto style_it = m_fill_styles.emplace(style);
		uint32_t style_index = (uint32_t)std::distance(m_fill_styles.begin(), style_it.first) + 1;

		m_edges.push_back({ style_index, edge });
	}

	void Shape::WriteXFL(XFL::XFLWriter& writer, uint32_t) const
	{
		DOM::Shape shape;
		XFL::XFLWriter shape_writer(writer, shape);

		WriteXFLStyles(shape_writer);
		WriteXFLEdges(shape_writer);
	}

	void Shape::WriteXFLStyles(XFL::XFLWriter& writer) const
	{
		auto fills = writer.CreateProperty(DOM::PropTag::Fills);

		uint32_t style_index = 1;
		for (auto& style : m_fill_styles)
		{
			DOM::FillStyle fill_style;
			fill_style.index = style_index;

			XFL::XFLWriter fill_root(fills, fill_style);
			std::visit([&fill_root](const auto& fill_style) {
				using T = std::decay_t<decltype(fill_style)>;

				if constexpr (std::is_same_v<T, Fill::SolidFillStyle>)
				{
					DOM::SolidColor style;
					style.color = fill_style.fill_color;

					XFL::XFLWriter style_writer(fill_root, style);
				}
				else if constexpr (std::is_same_v<T, Fill::BitmapFillStyle>)
				{
					// TODO: implement
				}
			}, style);
			style_index++;
		}
	}

	void Shape::WriteXFLEdges(XFL::XFLWriter & writer) const
	{
		auto edges = writer.CreateProperty(DOM::PropTag::Edges);

		for (const auto& [style_index, edge] : m_edges)
		{
			DOM::Edge edge_prop;
			edge_prop.fill_style_1 = style_index;
			edge_prop.edges = edge;
			XFL::XFLWriter(edges, edge_prop);
		}
	}
}