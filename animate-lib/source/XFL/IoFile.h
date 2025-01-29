#pragma once

#include "core/io/buffer_stream.h"

#include <filesystem>

namespace Animate::XFL
{
	class XflIoFile : public wk::BufferStream
	{
	public:
		void CompressChunked(void* buffer, size_t length, uint16_t chunk_size);
	};
}