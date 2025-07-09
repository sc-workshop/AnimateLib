#pragma once

#include "Animate/TypeTraits.h"
#include "Animate/Library/LibraryItem/Media/MediaBits.h"
#include "core/hashing/ncrypto/xxhash.h"

namespace Animate::Fill
{
	class BitmapFillStyle
	{
	public:
		Library::LibraryItemID bitmap;
		Matrix transform;

		bool operator ==(const BitmapFillStyle& other) const
		{
			return bitmap == other.bitmap && transform == other.transform;
		}
	};
}

namespace std {
	template <>
	struct hash<Animate::Fill::BitmapFillStyle> {
		size_t operator()(const Animate::Fill::BitmapFillStyle& style) const {
			auto path = style.bitmap.ToString();

			wk::hash::XxHash hasher;
			hasher.update((const uint8_t*)path.data(), path.size());
			hasher.update((uint8_t*)&style.transform.elements, sizeof(style.transform.elements));
			return hasher.digest();
		}
	};
}