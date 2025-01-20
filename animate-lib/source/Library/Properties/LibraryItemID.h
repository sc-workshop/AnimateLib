#pragma once

#include <stdint.h>
#include <time.h>
#include <string>

namespace Animate::Library
{
	class LibraryItemID
	{
	private:
		uint32_t s_RandomElement = 0;

	public:
		LibraryItemID() {};
		LibraryItemID(time_t high, uint32_t low) : m_high(high), m_low(low) {};

	public:
		void GenerateUniqueID();
		std::string ToString() const;
		void FromString(const std::string&);

	public:
		bool operator==(const LibraryItemID& other) const;
		bool operator!=(const LibraryItemID& other) const
		{
			return !(*this == other);
		}

	public:
		static LibraryItemID NoParent;
		static LibraryItemID NullItemID;

	private:
		time_t m_high = 0;
		uint32_t m_low = 0;
	};
}