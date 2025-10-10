#include "IoFile.h"

#include <zlib.h>
#include <vector>

namespace Animate::XFL
{
	void XflIoFile::CompressChunked(void* buffer, size_t length)
	{
		int result = 0;

		z_stream stream{};
		result = deflateInit(&stream, Z_BEST_SPEED);
		if (result != Z_OK)
		{
			throw wk::Exception("Failed to init ZStream");
		}

		Bytef stream_buffer[2048]{};

		stream.next_in = (Bytef*)buffer;
		stream.avail_in = (uInt)length;

		while (result != Z_STREAM_END)
		{
			stream.next_out = (Bytef*)&stream_buffer;
			stream.avail_out = sizeof(stream_buffer);

			result = deflate(&stream, 4 * (stream.total_in >= length));
			if ( 0 > result)
			{
				throw wk::Exception("Failed to compress data with error %i", Z_STREAM_ERROR);
			}

			
			if (stream.avail_out != sizeof(stream_buffer))
			{
				size_t buffer_length = sizeof(stream_buffer) - stream.avail_out;
				write_unsigned_short((uint16_t)buffer_length);
				write(&stream_buffer, buffer_length);
			}
		}

		write_unsigned_short(0);
		if (deflateEnd(&stream))
		{
			throw wk::Exception("Failed to close ZStream");
		}
	}
}
