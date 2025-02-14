#pragma once

#include "Stream.h"

#include "core/memory/ref.h"
#include "core/io/file_stream.h"

struct zip_t;

namespace Animate::IO
{
	class PackedStream final : public Stream
	{
	public:
		virtual ~PackedStream();

	public:
		virtual bool Open(const std::filesystem::path& path, OpenType type);
		virtual void Write(const std::filesystem::path& path, const void* data, size_t length);
		virtual void Flush();
		virtual bool Exist(const std::filesystem::path& path);

	private:
		std::vector<std::filesystem::path> m_written_files;
		wk::Unique<wk::Stream> m_file;
		zip_t* m_context = nullptr;
	};
}