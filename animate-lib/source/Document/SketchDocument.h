#pragma once

#include <filesystem>

#include "XFL/File.h"
#include "XFL/Writer.h"

#include "core/math/color_rgba.h"
#include "core/math/color_rgb.h"
#include "core/math/rect.h"

namespace Animate::Document
{
	class SketchDocument
	{	
	public:
		int GetFrameRate() const { return m_frameRate; };
		void SetFrameRate(const int rate) { m_frameRate = rate; };

		const wk::ColorRGB& GetBackgoundColor() const { return m_backgroundColor; };
		void SetBackgroundColor(const wk::ColorRGB color) { m_backgroundColor = color; };

		const wk::Rect& GetPaperBounds() const { return m_bounds; };
		void SetPaperBounds(const wk::Rect bound) { m_bounds = bound; };

	public:
		XFL::XFLWriter CreateXFLDOMWriter() const;
		void WriteXFL(const std::filesystem::path& path) const;
		void WriteXFLFolders(XFL::XFLWriter& writer) const;

	private:
		int m_frameRate = 24;
		wk::ColorRGB m_backgroundColor = {0xFF, 0xFF, 0XFF};
		wk::Rect m_bounds{0, 0, 1024, 1024};
	};
}