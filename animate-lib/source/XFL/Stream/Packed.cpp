#include "Packed.h"

#include "zip.h"

namespace fs = std::filesystem;

namespace Animate::IO
{
	PackedStream::~PackedStream()
	{
		if (m_context)
		{
			zip_close(m_context);
		}
	}

	bool PackedStream::Open(const fs::path& path, Stream::OpenType type)
	{
		int error = 0;

		if (type == Stream::OpenType::Write)
		{
			m_file = wk::CreateUnique<wk::OutputFileStream>(path);
			m_context = zip_stream_openwitherror(
				NULL, 0, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w', &error
			);
		}
		else
		{
			m_file = wk::CreateUnique<wk::InputFileStream>(path);
			m_context = zip_stream_openwitherror(
				(const char*)m_file->data(), m_file->length(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r', &error
			);
		}

		if (error != 0)
		{
			return false;
		}

		m_written_files.push_back(path);
		return true;
	}

	void PackedStream::Write(const fs::path& path, const void* data, size_t length)
	{
		zip_entry_open(m_context, path.string().c_str());
		zip_entry_write(m_context, data, length);
		zip_entry_close(m_context);
	}

	void PackedStream::Flush()
	{
		if (!m_file->is_writable() || !m_context) return;

		void* buffer = 0;
		size_t length = 0;

		zip_stream_copy(m_context, &buffer, &length);
		m_file->write(buffer, length);
	}

	bool PackedStream::Exist(const std::filesystem::path& path)
	{
		return std::find(m_written_files.begin(), m_written_files.end(), path) != m_written_files.end();
	}

	bool PackedStream::Writable()
	{
		return m_file->is_open();
	}
}