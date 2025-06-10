#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "core/math/color_rgb.h"
#include "core/math/color_rgba.h"
#include "core/math/matrix2d.h"
#include "core/math/matrix3d.h"

namespace Animate
{
	using String = std::string;

	template <typename T>
	using Container = std::vector<T>;

	using Path = std::filesystem::path;

	using Matrix = wk::Matrix2D;
	using Matrix3D = wk::Matrix3D;

	using Color = wk::ColorRGB;
	using ColorAlpha = wk::ColorRGBA;
} 