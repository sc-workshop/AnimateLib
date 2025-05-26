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
		XFLFile(const Path& path, IO::Stream::OpenType type);

	public:
		void SaveXFL(XFLWriter& writer);
		void SaveSymbol(XFLWriter& writer, const Path& path);
		void SaveBinary(const Path& path, XFL::XflIoFile& stream);
		bool Exist(const Path& path);

	public:
		Path GetLibraryItemPath(const Path& path);

	private:
		void CreateStream(IO::Stream::OpenType type);

	private:
		Ref<IO::Stream> m_stream;
		XFLType m_filetype;
		Path m_document_path;
	};
}