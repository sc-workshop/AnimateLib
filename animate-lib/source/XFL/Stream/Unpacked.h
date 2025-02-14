#pragma once

#include "Stream.h"

#include <filesystem>

namespace Animate::IO
{
	class UnpackedStream final : public Stream
	{
	public:
		virtual bool Open(const std::filesystem::path& path, OpenType type);
		virtual void Write(const std::filesystem::path& path, const void* data, size_t length);
		virtual void Flush() {};
		virtual bool Exist(const std::filesystem::path& path);

	private:
		void CreateBaseFolder(const std::filesystem::path& path);

	private:
		std::filesystem::path m_basedir;
	};
}