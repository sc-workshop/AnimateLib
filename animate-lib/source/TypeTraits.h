#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace Animate
{
	using String = std::string;

	template <typename T>
	using Container = std::vector<T>;

	using Path = std::filesystem::path;
} 