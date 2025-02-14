#include "Unpacked.h"

#include "core/io/file_stream.h"

namespace fs = std::filesystem;

namespace Animate::IO
{
	bool UnpackedStream::Open(const std::filesystem::path& path, Stream::OpenType type)
	{
		if (!fs::exists(path))
		{
			if (type == Stream::OpenType::Write)
			{
				fs::create_directories(path);
			}
			else
			{
				return false;
			}
			
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

	bool UnpackedStream::Writable()
	{
		fs::path basename = m_basedir.stem().concat(".xfl");
		fs::path proxy = m_basedir / basename;
		if (!fs::exists(proxy))
		{
			return false;
		}

		std::ofstream file(proxy, std::ios_base::app);
		return file.good();
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