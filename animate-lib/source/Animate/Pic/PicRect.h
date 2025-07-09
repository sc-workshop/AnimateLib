#pragma once

#include "PicShape.h"

#include "Animate/XFL/DOM/Fill/RectangleObject.h"

namespace Animate::Pic
{
	class Rectangle : public Shape
	{
	public:
		virtual bool IsPicRect() const { return true; };

	public:
		void SetPrimitiveBound(const Bound& bound) { m_rectangle = bound; }
		void SetPrimitiveFill(const FillStyle& style) { m_style = style; }

	public:
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t /*index*/) const;

	private:
		Bound m_rectangle;
		FillStyle m_style;
	};
}