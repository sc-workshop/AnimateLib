#pragma once

#include <string>
#include <vector>
#include <list>
#include <filesystem>
#include <array>

#include "core/math/color_rgb.h"
#include "core/math/color_rgba.h"
#include "core/math/matrix2d.h"
#include "core/math/matrix3d.h"
#include "core/math/rect.h"
#include "core/math/point.h"

namespace Animate
{
	using String = std::string;

	template <typename T>
	using Container = std::vector<T>;

	template <typename T>
	using List = std::list<T>;

	using Path = std::filesystem::path;

	using Matrix = wk::Matrix2D;
	using Matrix3D = wk::Matrix3D;

	using Color = wk::ColorRGB;
	using ColorAlpha = wk::ColorRGBA;

	using Bound = wk::RectF;
	using Range = wk::Point_t<size_t>;
	using RangeF = wk::Point_t<float>;

	using Point2D = wk::Point_t<float>;

	struct GUID {
		uint32_t data1;
		uint16_t data2;
		uint16_t data3;
		std::array<uint8_t, 8> data4;
	};
	
	struct DocumentType {
		std::string name;
		GUID documentId;
	};
}