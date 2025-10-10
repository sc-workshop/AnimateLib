#include "SketchDocument.h"

#include "core/platform/platform_info.h"

namespace Animate::Document
{
	SketchDocument::SketchDocument() : m_controller(*this)
	{

	}

	void SketchDocument::SetCurrentDocPageForSymDependCache(const Library::LibraryItem* item)
	{
		m_cache.SetCurrentDocPage(item);
	}

	bool SketchDocument::WriteSymDependCacheToXFL(XFL::XFLFile& file) const
	{
		if (m_cache)
			return m_cache.WriteXFL(file);

		return false;
	}

	void SketchDocument::AddSymbolReferenceToSymDependCache(Library::LibraryItem& item)
	{
		m_cache.AddSymbolReference(item);
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
			versionInfo << "Saved by Animate Lib (SC WORKSHOP) ";
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

	void SketchDocument::WriteXFL(const Path& path) const
	{
		XFL::XFLFile file(path, IO::Stream::OpenType::Write);
		auto writer = CreateXFLDOMWriter();

		WriteXFLFolders(file, writer);
		WriteXFLMedia(file, writer);
		WriteXFLSymbols(file, writer);

		WriteSymDependCacheToXFL(file);
		
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

		for (size_t i = 0; symbols.Length() > i; i++)
		{
			auto& item = symbols[i];
			item.WriteXFL(file, items);
		}

		size_t count = symbols.Length();
		auto begin = symbols.begin();
		auto seq = GetSavePool().submit_sequence(0, count, [begin, &file](size_t i) {
			auto it = begin;
			std::advance(it, i);

			(*it)->WriteXFLSymbol(file);

		}, BS::pr::high);
		seq.wait();
	}
}