#pragma once

#include "Stream.h"

#include "core/memory/ref.h"
#include "core/io/file_stream.h"

#include <mutex>

struct zip_t;

namespace Animate::IO
{
	class PackedStream final : public Stream
	{
	public:
		virtual ~PackedStream();

	public:
		virtual bool Open(const Path& path, OpenType type);
		virtual void Flush();
		virtual bool Exist(const Path& path);
		virtual bool Writable();

		virtual bool OpenFile(const Path& path);
		virtual size_t WriteFile(const void* data, size_t length);
		virtual void CloseFile();

	private:
		std::mutex m_mutex;
		std::vector<Path> m_written_files;
		wk::Unique<wk::Stream> m_file;
		zip_t* m_context = nullptr;
	};
}