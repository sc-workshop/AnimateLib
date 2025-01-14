#pragma once

#include "core/io/stream.h"
#include <filesystem>

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
		virtual bool Open(const std::filesystem::path& path, OpenType type) = 0;
		virtual void Write(const std::filesystem::path& path, const void* data, size_t length) = 0;
		virtual void Flush() = 0;

		void Write(const std::filesystem::path& path, wk::Stream& stream)
		{
			Write(path, stream.data(), stream.length());
		}
	};
}