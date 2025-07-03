#pragma once

#include "Animate/TypeTraits.h"
#include "Animate/Library/LibraryItem/Media/MediaBits.h"
#include "core/hashing/ncrypto/xxhash.h"

namespace Animate::Fill
{
	class BitmapFillStyle
	{
	public:
		Library::MediaBits& bitmap;

		bool operator ==(const BitmapFillStyle& other) const
		{
			return bitmap.GetItemPath() == other.bitmap.GetItemPath();
		}
	};
}

namespace std {
	template <>
	struct hash<Animate::Fill::BitmapFillStyle> {
		size_t operator()(const Animate::Fill::BitmapFillStyle& style) const {
			auto path = style.bitmap.GetItemPath().string();

			wk::hash::XxHash hasher;
			hasher.update((const uint8_t*)path.data(), path.size());
			return hasher.digest();
		}
	};
}