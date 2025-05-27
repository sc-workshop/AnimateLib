#pragma once

#include "Stream.h"

#include <filesystem>

namespace Animate::IO
{
	class UnpackedStream final : public Stream
	{
	public:
		virtual bool Open(const Path& path, OpenType type);
		virtual void Write(const Path& path, const void* data, size_t length);
		virtual void Flush() {};
		virtual bool Exist(const Path& path);
		virtual bool Writable();

	private:
		void CreateBaseFolder(const Path& path);

	private:
		Path m_basedir;
	};
}