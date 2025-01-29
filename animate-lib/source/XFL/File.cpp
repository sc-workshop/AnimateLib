#include "File.h"

namespace fs = std::filesystem;

namespace Animate::XFL
{
	XFLFile::XFLFile(const std::filesystem::path & path, IO::Stream::OpenType type)
	{
		m_filetype = path.extension() == ".xfl" ? XFLType::Unpacked : XFLType::Packed;

		if (m_filetype == XFLType::Unpacked)
		{
			m_document_path = path.parent_path();
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

		document.Save("DOMDocument.xml", *m_stream);

		m_stream->Flush();
	}

	void XFLFile::SaveBinary(std::filesystem::path path, XFL::XflIoFile& stream)
	{
		std::filesystem::path filepath = "bin" / path;
		m_stream->Write(filepath, stream);
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