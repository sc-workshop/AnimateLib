#include "IoFile.h"

#include <zlib.h>
#include <vector>

namespace Animate::XFL
{
	void XflIoFile::CompressChunked(void* buffer, size_t length, uint16_t chunk_size)
	{
		int result = 0;

		z_stream stream{};
		result = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
		if (result != Z_OK)
		{
			throw wk::Exception("Failed to init ZStream");
		}

		std::vector<char> chunk_buffer;
		chunk_buffer.resize(chunk_size);

		stream.next_in = (Bytef*)buffer;
		stream.avail_in = (uInt)length;

		while (result != Z_STREAM_END)
		{
			stream.next_out = (Bytef*)chunk_buffer.data();
			stream.avail_out = (uInt)chunk_buffer.size();

			result = deflate(&stream, 4 * (stream.total_in >= length));
			if ( 0 > result)
			{
				throw wk::Exception("Failed to compress data with error %i", Z_STREAM_ERROR);
			}

			if (stream.avail_out != chunk_size)
			{
				uint16_t buffer_length = uint16_t(chunk_size - stream.avail_out);
				write_unsigned_short(buffer_length);
				write(chunk_buffer.data(), buffer_length);
			}
		}

		write_unsigned_short(0);
		if (deflateEnd(&stream))
		{
			throw wk::Exception("Failed to close ZStream");
		}
	}
}
