#include "Unpacked.h"
#include "assert.h"

namespace fs = std::filesystem;

namespace Animate::IO
{
	bool UnpackedStream::Open(const Path& path, Stream::OpenType type)
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

	bool UnpackedStream::Exist(const Path& path)
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

	bool UnpackedStream::OpenFile(const Path& path)
	{
		//assert(m_active_file == nullptr);

		fs::path destination = m_basedir;
		destination /= path;
		CreateBaseFolder(destination);

		m_mutex.lock();
		m_active_file = wk::CreateRef<wk::OutputFileStream>(destination);
		return true;
	}

	size_t UnpackedStream::WriteFile(const void* data, size_t length)
	{
		if (!m_active_file) return 0;

		return m_active_file->write(data, length);
	}

	void UnpackedStream::CloseFile()
	{
		m_active_file.reset();
		m_mutex.unlock();
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