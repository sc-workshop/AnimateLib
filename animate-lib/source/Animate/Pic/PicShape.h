#pragma once

#include <variant>
#include <unordered_set>

#include "PicObject.h"

#include "Animate/Fill/Style/SolidColor.h"
#include "Animate/Fill/Style/Bitmap.h"

namespace Animate::Pic
{
	class Shape : public Object
	{
	public:
		using FillStyle = std::variant<Fill::SolidFillStyle, Fill::BitmapFillStyle>;

		struct Edge
		{
			uint32_t style = 0;
			bool is_hole = false;
			std::string contour;
		};

	public:
		virtual bool IsPicShape() const { return true; };

	public:
		void CreateEdge(const FillStyle& style, const std::string& edge, bool is_hole = false);
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t /*index*/) const;
		void WriteXFLStyles(XFL::XFLWriter& writer) const;
		void WriteXFLStyle(XFL::XFLWriter& writer, const FillStyle& style, uint32_t index = 0) const;
		void WriteXFLEdges(XFL::XFLWriter& writer) const;

	protected:
		virtual Object* CloneObject()
		{
			return new Shape(*this);
		}

	private:
		std::unordered_set<FillStyle> m_fill_styles;
		std::vector<Edge> m_edges;
	};
}