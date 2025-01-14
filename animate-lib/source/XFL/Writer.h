#pragma once

#include "SerizalizeTraits.h"
#include "Stream/Stream.h"
#include <filesystem>

#include "core/memory/ref.h"
#include "core/exception/exception.h"

namespace Animate::DOM
{
	class DOMElement;
}

namespace Animate::XFL
{
	class XFLWriter
	{
	public:
		XFLWriter(DOM::DOMElement& element);
		XFLWriter(DOM::Node node, DOM::DOMElement& element, bool isRoot = false);

	public:
		void Save(const std::filesystem::path& path, IO::Stream& stream);

	public:
		template<
			typename T,
			typename std::enable_if_t<
			std::is_enum_v<T> ||
			std::is_arithmetic_v<T> ||
			std::is_pointer_v<T>
			, bool> = true>
		void WriteAttr(const std::string& name, const T& value, const T& default_value = 0)
		{
			if (value == default_value) return;

			m_node.append_attribute(name)
					.set_value(value);
		}
		
	private:
		void InitializeNode(DOM::DOMElement& element, bool isRoot = false);

	private:
		DOM::Node m_node;
		wk::Ref<DOM::Document> m_root;
	};
}