#include "SketchDocument.h"

#include "XFL/File.h"

namespace Animate::Document
{
	XFL::XFLWriter SketchDocument::CreateXFLDOMWriter() const
	{
		DOM::FLDocument document;
		document.xflVersion = "23.0";
		document.frameRate = GetFrameRate();
		document.backgroundColor = GetBackgoundColor();

		return XFL::XFLWriter(document);
	}

	void SketchDocument::WriteXFL(const std::filesystem::path& path) const
	{
		XFL::XFLFile file(path, IO::Stream::OpenType::Write);
		auto writer = CreateXFLDOMWriter();
		
		file.SaveXFL(writer);
	}
}