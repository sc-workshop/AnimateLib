#include "SketchDocument.h"

#include "core/platform/platform_info.h"

namespace Animate::Document
{
	SketchDocument::SketchDocument() : m_controller(*this)
	{

	}

	XFL::XFLWriter SketchDocument::CreateXFLDOMWriter() const
	{
		DOM::FLDocument document;
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

		WriteXFLFolders(file, writer);
		WriteXFLMedia(file, writer);
		WriteXFLSymbols(file, writer);
		
		file.SaveXFL(writer);
	}

	void SketchDocument::WriteXFLFolders(XFL::XFLFile& file, XFL::XFLWriter& writer) const
	{
		XFL::XFLProp items = writer.CreateProperty(DOM::PropTag::Folders);

		for (size_t i = 0; libraryFolders.Length() > i; i++)
		{
			auto& item = libraryFolders[i];
			item.WriteXFL(file, items);
		}
	}
	void SketchDocument::WriteXFLMedia(XFL::XFLFile& file, XFL::XFLWriter& writer) const
	{
		XFL::XFLProp items = writer.CreateProperty(DOM::PropTag::Media);

		for (size_t i = 0; mediaElements.Length() > i; i++)
		{
			auto& item = mediaElements[i];
			item.WriteXFL(file, items);

			XFL::XflIoFile media_file;
			item.WriteXFLContent(media_file);

			fs::path media_path = item.GetXFLMediaPath();
			file.SaveBinary(media_path, media_file);
		}
	}

	void SketchDocument::WriteXFLSymbols(XFL::XFLFile& file, XFL::XFLWriter& writer) const
	{
		XFL::XFLProp items = writer.CreateProperty(DOM::PropTag::Symbols);

		// TODO: add multithreading for that loop ? or at least for symbol writing
		for (size_t i = 0; symbols.Length() > i; i++)
		{
			auto& item = symbols[i];
			item.WriteXFL(file, items);
			item.WriteXFLSymbol(file);
		}
	}
}