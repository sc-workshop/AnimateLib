#pragma once

#include <string>

namespace Animate::Library
{
	class LinkageProps
	{
	public:
		std::string GetIdentifier() const { return m_identifier; }
		void SetIdentifier(const std::string& id) { m_identifier = id; }

		std::string GetClass() const { return m_class; }
		void SetClass(const std::string& name) { m_class = name; }

		std::string GetBaseClass() const { return m_baseClass; }
		void SetBaseClass(const std::string& name) { m_baseClass = name; }

	private:
		std::string m_identifier;
		std::string m_class;
		std::string m_baseClass;
	};
}