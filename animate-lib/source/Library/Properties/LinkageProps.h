#pragma once

#include "TypeTraits.h"

namespace Animate::Library
{
	class LinkageProps
	{
	public:
		String GetIdentifier() const { return m_identifier; }
		void SetIdentifier(const String& id) { m_identifier = id; }

		String GetClass() const { return m_class; }
		void SetClass(const String& name) { m_class = name; }

		String GetBaseClass() const { return m_baseClass; }
		void SetBaseClass(const String& name) { m_baseClass = name; }

	private:
		String m_identifier;
		String m_class;
		String m_baseClass;
	};
}