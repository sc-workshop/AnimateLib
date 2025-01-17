#include "SketchDocument.h"

#include "core/platform/platform_info.h"

namespace Animate::Document
{
	XFL::XFLWriter SketchDocument::CreateXFLDOMWriter() const
	{
		DOM::FLDocument document{};
		document.xflVersion = "23.0";
		document.creator = "Adobe Animate Lib";
		document.platform = wk::CurrentPlatformName();

		// TODO: add more right versioning?
		document.majorVersion = 23;
		document.buildNumber = 0;
		document.minorVersion = 0;

		{
			std::stringstream versionInfo;
			versionInfo << "Saved by Animate Lib ";
			versionInfo << document.platform;
			versionInfo << " " << document.majorVersion << " ";
			versionInfo << "build " << document.buildNumber;

			document.versionInfo = versionInfo.str();
		}

		document.frameRate = GetFrameRate();
		document.backgroundColor = GetBackgoundColor();

		document.width = std::abs(m_bounds.x - m_bounds.width);
		document.height = std::abs(m_bounds.y - m_bounds.height);

		return XFL::XFLWriter(document);
	}

	void SketchDocument::WriteXFL(const std::filesystem::path& path) const
	{
		XFL::XFLFile file(path, IO::Stream::OpenType::Write);
		auto writer = CreateXFLDOMWriter();

		WriteXFLFolders(writer);
		
		file.SaveXFL(writer);
	}

	void SketchDocument::WriteXFLFolders(XFL::XFLWriter& writer) const
	{
		XFL::XFLProp property = writer.CreateProperty(DOM::PropTag::Folders);

	}
}