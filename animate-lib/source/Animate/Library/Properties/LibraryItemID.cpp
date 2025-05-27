#include "LibraryItemID.h"

#include "core/string/string_converter.h"

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

	String LibraryItemID::ToString() const
	{
		auto left = wk::StringConverter::ToHex(m_high);
		wk::StringConverter::StripLeadingHexZeros(left);

		auto right = wk::StringConverter::ToHex(m_low);
		return left + "-" + right;
	}

	void LibraryItemID::FromString(const String&)
	{
		// TODO
	}

	LibraryItemID LibraryItemID::NoParent = { 0, 0xFFFFFFFF };
	LibraryItemID LibraryItemID::NullItemID = { 0, 0 };
}