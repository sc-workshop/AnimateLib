#pragma once

#include <filesystem>

#include "XFL/File.h"

namespace Animate::Document
{
	class SketchDocument
	{
	public:
		int GetFrameRate() const;
		void SetFrameRate(int rate);

	public:
		XFL::XFLWriter CreateXFLDOMWriter() const;
		void WriteXFL(const std::filesystem::path& path) const;

	private:
		int m_frameRate = 30;
	};
}