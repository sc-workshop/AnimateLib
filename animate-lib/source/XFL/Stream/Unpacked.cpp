#include "Unpacked.h"

#include "core/io/file_stream.h"

namespace fs = std::filesystem;

namespace Animate::IO
{
	bool UnpackedStream::Open(const std::filesystem::path& path, Stream::OpenType /*type*/)
	{
		if (!fs::exists(path))
		{
			fs::create_directories(path);
		}

		m_basedir = path;
		return true;
	}

	void UnpackedStream::Write(const fs::path& path, const void* data, size_t length)
	{
		fs::path destination = m_basedir;
		destination /= path;
		CreateBaseFolder(destination);

		wk::OutputFileStream file(destination);
		file.write(data, length);
	}

	bool UnpackedStream::Exist(const std::filesystem::path& path)
	{
		return fs::exists(m_basedir / path);
	}

	void UnpackedStream::CreateBaseFolder(const fs::path& path)
	{
		fs::path base = path.parent_path();
		if (!fs::exists(base))
		{
			fs::create_directories(base);
		}
	}
}