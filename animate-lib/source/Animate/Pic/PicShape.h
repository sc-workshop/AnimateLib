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
		virtual bool IsPicShape() const override { return true; };

	public:
		void ConvertToDrawingObject() { m_is_object = true; }
		void CreateEdge(const FillStyle& style, const std::string& edge, bool is_hole = false, bool merge_edges = true);
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t /*index*/) const override;
		void WriteXFLStyles(XFL::XFLWriter& writer) const;
		void WriteXFLStyle(XFL::XFLWriter& writer, const FillStyle& style, uint32_t index = 0) const;
		void WriteXFLEdges(XFL::XFLWriter& writer) const;

	public:
		virtual bool GetMatrix(Matrix& matrix) const override {
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
			return new Shape(*this);
		}

	private:
		Matrix m_matrix;
		std::vector<FillStyle> m_fill_styles;
		std::vector<Edge> m_edges;
		bool m_is_object = false;
	};
}