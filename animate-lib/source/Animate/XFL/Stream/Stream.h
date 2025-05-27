#pragma once

#include "core/io/stream.h"
#include "Animate/TypeTraits.h"

namespace Animate::IO
{
	class Stream
	{
	public:
		enum class OpenType
		{
			Read,
			Write
		};

	public:
		virtual ~Stream() = default;

	public:
		virtual bool Open(const Path& path, OpenType type) = 0;
		virtual void Write(const Path& path, const void* data, size_t length)
		{
			if (!OpenFile(path))
			{
				throw wk::Exception("Failed to open file for writing: " + path.string());
			}

			if (WriteFile(data, length) != length)
			{
				throw wk::Exception("Failed to write data to file: " + path.string());
			}

			CloseFile();
		};

		void Write(const Path& path, wk::Stream& stream)
		{
			Write(path, stream.data(), stream.length());
		}

		virtual void Flush() = 0;
		virtual bool Exist(const Path& path) = 0;
		virtual bool Writable() = 0;

		virtual bool OpenFile(const Path& path) = 0;
		virtual size_t WriteFile(const void* data, size_t length) = 0;
		virtual void CloseFile() = 0;
	};
}