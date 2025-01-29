#pragma once

#include "core/memory/ref.h"
#include "core/exception/exception.h"
#include <filesystem>

#include "Stream/Packed.h"
#include "Stream/Unpacked.h"
#include "IoFile.h"
#include "Writer.h"
#include "DOM/Document/DOMDocument.h"

namespace Animate::XFL
{
	using namespace wk;

	class XFLFile
	{
	private:
		enum class XFLType
		{
			Unpacked,
			Packed
		};

	public:
		XFLFile(const std::filesystem::path& path, IO::Stream::OpenType type);

	public:
		void SaveXFL(XFLWriter& writer);
		void SaveBinary(std::filesystem::path path, XFL::XflIoFile& stream);

	private:
		void CreateStream(IO::Stream::OpenType type);

	private:
		Ref<IO::Stream> m_stream;
		XFLType m_filetype;
		std::filesystem::path m_document_path;
	};
}