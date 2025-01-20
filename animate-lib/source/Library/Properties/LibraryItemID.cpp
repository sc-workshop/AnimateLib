#include "LibraryItemID.h"

namespace Animate::Library
{
	void LibraryItemID::GenerateUniqueID()
	{
		time(&m_high);
		m_low = ++s_RandomElement;
	}

	bool LibraryItemID::operator==(const LibraryItemID& other) const
	{
		return m_high == other.m_high && m_low == other.m_low;
	}

	std::string LibraryItemID::ToString() const
	{
		// TODO
		return "";
	}

	void LibraryItemID::FromString(const std::string&)
	{
		// TODO
	}

	LibraryItemID LibraryItemID::NoParent = { 0, 0xFFFFFFFF };
	LibraryItemID LibraryItemID::NullItemID = { 0, 0 };
}