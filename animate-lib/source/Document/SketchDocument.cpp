#include "SketchDocument.h"

#include "core/platform/platform_info.h"

namespace Animate::Document
{
	SketchDocument::SketchDocument() : m_controller(*this)
	{

	}

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
		WriteXFLMedia(writer);
		
		file.SaveXFL(writer);
	}

	void SketchDocument::WriteXFLFolders(XFL::XFLWriter& writer) const
	{
		XFL::XFLProp folders = writer.CreateProperty(DOM::PropTag::Folders);

		for (size_t i = 0; libraryFolders.Length() > i; i++)
		{
			auto& item = libraryFolders.At(i);
			item.WriteXFL(folders);
		}
	}
	void SketchDocument::WriteXFLMedia(XFL::XFLWriter& writer) const
	{
		XFL::XFLProp media = writer.CreateProperty(DOM::PropTag::Media);

		for (size_t i = 0; mediaElements.Length() > i; i++)
		{
			auto& item = mediaElements.At(i);
			item.WriteXFL(media);
		}
	}
}