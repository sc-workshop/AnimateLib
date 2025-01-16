#pragma once

#include <filesystem>

#include "XFL/File.h"

#include "core/math/color_rgba.h"
#include "core/math/color_rgb.h"

namespace Animate::Document
{
	class SketchDocument
	{	
	public:
		int GetFrameRate() const { return m_frameRate; };
		void SetFrameRate(const int rate) { m_frameRate = rate; };

		const wk::ColorRGB& GetBackgoundColor() const { return m_backgroundColor; };
		void SetBackgroundColor(const wk::ColorRGB color) { m_backgroundColor = color; };

	public:
		XFL::XFLWriter CreateXFLDOMWriter() const;
		void WriteXFL(const std::filesystem::path& path) const;

	private:
		int m_frameRate = 30;
		wk::ColorRGB m_backgroundColor = {0xFF, 0xFF, 0XFF};
	};
}