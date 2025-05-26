#pragma once

#include "core/io/stream.h"
#include "TypeTraits.h"

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
		virtual void Write(const Path& path, const void* data, size_t length) = 0;
		virtual void Flush() = 0;
		virtual bool Exist(const Path& path) = 0;
		virtual bool Writable() = 0;

		void Write(const Path& path, wk::Stream& stream)
		{
			Write(path, stream.data(), stream.length());
		}
	};
}