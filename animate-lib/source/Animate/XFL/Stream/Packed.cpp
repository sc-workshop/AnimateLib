#include "Packed.h"
#include "assert.h"

#include <algorithm>

namespace fs = std::filesystem;
using MemoryIStream = std::istream;

namespace Animate::IO
{
	static zip_int64_t zip_memory_source(
		void* userdata,
		void* data,
		zip_uint64_t len,
		zip_source_cmd_t cmd
	) {
		PackedStream* mem = static_cast<PackedStream*>(userdata);

		switch (cmd) {
		case ZIP_SOURCE_OPEN:
			return 0;

		case ZIP_SOURCE_CLOSE:
			return 0;

		case ZIP_SOURCE_BEGIN_WRITE:
		case ZIP_SOURCE_COMMIT_WRITE:
			return 0;

		case ZIP_SOURCE_WRITE:
			return static_cast<zip_int64_t>(mem->stream->write(data, len));

		case ZIP_SOURCE_READ:
			return static_cast<zip_int64_t>(mem->stream->read(data, len));

		case ZIP_SOURCE_TELL:
			return static_cast<zip_int64_t>(mem->stream->length());

		case ZIP_SOURCE_SEEK_WRITE: {
			zip_source_args_seek_t* args = reinterpret_cast<zip_source_args_seek_t*>(data);
			switch (args->whence) {
			case SEEK_SET:
				mem->stream->seek(args->offset);
				break;
			case SEEK_CUR:
				mem->stream->seek(args->offset, wk::Stream::SeekMode::Add);
				break;
			case SEEK_END:
				mem->stream->seek(mem->stream->length() - args->offset);
				break;
			}

			mem->stream->seek(args->offset);
			return 0;
		}
		case ZIP_SOURCE_TELL_WRITE:
			return static_cast<zip_int64_t>(mem->stream->position());

		case ZIP_SOURCE_STAT: {
			auto* st = static_cast<zip_stat_t*>(data);
			zip_stat_init(st);
			st->size = mem->stream->length();
			st->valid = ZIP_STAT_SIZE;
			return sizeof(zip_stat_t);
		}

		case ZIP_SOURCE_ERROR:
			zip_error_to_data(mem->error, data, len);
			return sizeof(zip_error_t);

		case ZIP_SOURCE_FREE:
			return 0;

		case ZIP_SOURCE_SEEK:
		case ZIP_SOURCE_SUPPORTS:
			if (mem->stream->is_writable())
				return ZIP_SOURCE_SUPPORTS_WRITABLE;

			return ZIP_SOURCE_SUPPORTS_READABLE;

		default:
			return -1;
		}
	}

	PackedStream::PackedStream()
	{
		error = new zip_error();
		zip_error_init(error);
	}

	PackedStream::~PackedStream()
	{
		zip_error_fini(error);
		if (error)
			delete error;

	}

	bool PackedStream::Open(const Path& path, OpenType type)
	{
		auto& manager = wk::AssetManager::Instance();

		// Initialize stream
		if (type == Stream::OpenType::Write)
		{
			stream = manager.write_file(path);
		}
		else {
			stream = manager.load_file(path);
		}

		// Initialize reader
		source = zip_source_function_create(
			zip_memory_source, this, error
		);
		
		// Initialize zip
		if (type == Stream::OpenType::Write)
		{
			m_zip = zip_open_from_source(source, ZIP_CREATE | ZIP_TRUNCATE, error);
		}
		else {
			m_zip = zip_open_from_source(source, ZIP_RDONLY, error);
		}
		
		return true;
	}

	void PackedStream::Close()
	{
		if (!stream->is_writable()) return;

		if (zip_close(m_zip) < 0)
			throw wk::Exception("Failed to finalize packed stream");
	}

	bool PackedStream::Exist(const Path& path)
	{
		return std::find(m_written_files.begin(), m_written_files.end(), path) != m_written_files.end();
	}

	bool PackedStream::Writable()
	{
		return stream->is_open();
	}

	bool PackedStream::OpenFile(const Path& path) {
		m_mutex.lock();
		m_path = path;

		return true;
	}

	size_t PackedStream::WriteFile(const void* data, size_t length) {
		m_buffer.insert(m_buffer.end(), (const uint8_t*)data, (const uint8_t*)data + length);
		return length;
	}

	void PackedStream::CloseFile() {
		void* data = wk::Memory::allocate(m_buffer.size());
		std::memcpy(data, m_buffer.data(), m_buffer.size());

		zip_source_t* buffer = nullptr;
		if ((buffer = zip_source_buffer(m_zip, data, m_buffer.size(), 1)) == NULL) {
			Cleanup();
			std::free(data);
			throw wk::Exception("Failed to open source ZIP buffer");
		}

		zip_int64_t idx = -1;
		if ((idx = zip_file_add(m_zip, m_path.generic_string().c_str(), buffer, ZIP_FL_ENC_UTF_8)) == -1) {
			zip_error_t* err = zip_get_error(m_zip);
			zip_source_free(buffer);
			Cleanup();
			throw wk::Exception("Failed to add ZIP buffer: %s", zip_error_strerror(err));
		}

		zip_set_file_compression(
			m_zip,
			idx,
			ZIP_CM_DEFLATE,
			2
		);

		Cleanup();
	}

	void PackedStream::Cleanup()
	{
		m_buffer.clear();
		m_path = "";
		m_mutex.unlock();
	}
}