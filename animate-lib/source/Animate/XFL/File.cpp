#include "File.h"

namespace fs = std::filesystem;

namespace Animate::XFL
{
	XFLFile::XFLFile(const Path & path, IO::Stream::OpenType type)
	{
		m_filetype = path.extension() == ".xfl" ? XFLType::Unpacked : XFLType::Packed;

		if (m_filetype == XFLType::Unpacked)
		{
			m_document_path = path;
			m_document_path.replace_extension("");
		}
		else
		{
			m_document_path = path;
		}

		CreateStream(type);
	}

	void XFLFile::SaveXFL(XFLWriter& document)
	{
		fs::path proxy = m_document_path.stem();
		const std::string proxy_content = "PROXY-CS5";
		m_stream->Write(proxy.concat(".xfl"), proxy_content.c_str(), proxy_content.size());

		if (!m_stream->Writable())
		{
			throw wk::Exception("Failed to save. Target project is not writable");
		}

		document.Save("DOMDocument.xml", *m_stream);

		m_stream->Flush();
	}

	void XFLFile::SaveSymbol(XFLWriter& document, const Path& path)
	{
		Path symbol_path = GetLibraryItemPath(path);
		document.Save(symbol_path, *m_stream);
	}

	void XFLFile::SaveBinary(const Path& path, XFL::XflIoFile& stream)
	{
		Path filepath = "bin" / path;
		m_stream->Write(filepath, stream);
	}

	bool XFLFile::Exist(const Path& path)
	{
		return m_stream->Exist(path);
	}

	Path XFLFile::GetLibraryItemPath(const Path& path)
	{
		return (Path("LIBRARY") / path).concat(".xml");
	}

	void XFLFile::CreateStream(IO::Stream::OpenType type)
	{
		if (m_filetype == XFLType::Packed)
		{
			m_stream = CreateRef<IO::PackedStream>();
		}
		else
		{
			m_stream = CreateRef<IO::UnpackedStream>();
		}

		if (!m_stream->Open(m_document_path, type))
		{
			throw Exception("Failed to open XFL file");
		}
	}
}