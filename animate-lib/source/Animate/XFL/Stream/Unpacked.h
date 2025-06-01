#pragma once

#include "Stream.h"

#include <filesystem>
#include "core/memory/ref.h"
#include "core/io/file_stream.h"

#include <mutex>

namespace Animate::IO
{
	class UnpackedStream final : public Stream
	{
	public:
		virtual bool Open(const Path& path, OpenType type);
		virtual void Flush() {};
		virtual bool Exist(const Path& path);
		virtual bool Writable();

		virtual bool OpenFile(const Path& path);
		virtual size_t WriteFile(const void* data, size_t length);
		virtual void CloseFile();

	private:
		void CreateBaseFolder(const Path& path);

	private:
		std::mutex m_mutex;
		Path m_basedir;
		wk::Ref<wk::OutputFileStream> m_active_file;
	};
}