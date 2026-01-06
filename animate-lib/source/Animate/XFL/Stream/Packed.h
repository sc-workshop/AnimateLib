#pragma once

#include "Stream.h"

#include "core/memory/ref.h"
#include "core/asset_manager/asset_manager.h"

#include <zip.h>
#include <mutex>

namespace Animate::IO
{
	//class OutputStream : public std::streambuf {
	//public:
	//	explicit OutputStream(wk::Ref<wk::Stream> stream) : m_stream(stream) {
	//		setp(nullptr, nullptr);
	//	}
	//
	//protected:
	//	int_type overflow(int_type ch) override {
	//		if (ch != traits_type::eof()) {
	//			m_stream->write(reinterpret_cast<const char*>(&ch), 1);
	//			return ch;
	//		}
	//		return traits_type::eof();
	//	}
	//
	//	std::streamsize xsputn(const char* s, std::streamsize count) override {
	//		return m_stream->write(s, count);
	//	}
	//
	//private:
	//	wk::Ref<wk::Stream> m_stream;
	//};
	//
	//class InputStream : public std::streambuf {
	//public:
	//	InputStream(const void* base, std::size_t size) {
	//		char* p = (char*)const_cast<void*>(base);
	//		setg(p, p, p + size);
	//	}
	//};

	class PackedStream final : public Stream
	{
	public:
		PackedStream();
		virtual ~PackedStream();

	public:
		virtual bool Open(const Path& path, OpenType type);
		virtual void Close();
		virtual bool Exist(const Path& path);
		virtual bool Writable();

		virtual bool OpenFile(const Path& path);
		virtual size_t WriteFile(const void* data, size_t length);
		virtual void CloseFile();

		void Cleanup();

		wk::Ref<wk::Stream> stream;
		zip_error_t* error = nullptr;
		zip_source_t* source = nullptr;

	private:
		std::mutex m_mutex;

		std::filesystem::path m_path;
		std::vector<uint8_t> m_buffer;
		std::vector<Path> m_written_files;
		
		zip_t* m_zip = nullptr;		
	};
}