#pragma once

#include "SerizalizeTraits.h"
#include "Stream/Stream.h"
#include "DOM/DOMProps.h"

#include <filesystem>
#include <string>
#include <sstream>
#include <iomanip>

#include "core/memory/ref.h"
#include "core/exception/exception.h"

#include "core/math/color_rgb.h"
#include "core/math/color_rgba.h"

namespace Animate::DOM
{
	class DOMElement;
}

namespace Animate::XFL
{
	class XFLWriter;
	using XFLProp = XFLWriter;

	class XFLWriter
	{
	public:
		XFLWriter(DOM::DOMElement& element);;
		XFLWriter(DOM::Node node, DOM::DOMElement& element);
		XFLWriter(DOM::Node node, DOM::PropTag prop);

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

		void WriteAttr(const std::string& name, const wk::ColorRGB& value, const wk::ColorRGB default_value = {0xFF, 0xFF, 0xFF})
		{
			if (value == default_value) return;

			DOM::Attribute attr = m_node.append_attribute(name);
			WriteColorAttr<wk::ColorRGB, false>(attr, value);
		}

		void WriteAttr(const std::string& name, const wk::ColorRGBA& value, bool write_alpha = false, const wk::ColorRGBA default_value = { 0xFF, 0xFF, 0xFF, 0xFF })
		{
			if (value == default_value) return;

			DOM::Attribute attr = m_node.append_attribute(name);
			write_alpha ? WriteColorAttr<wk::ColorRGBA, true>(attr, value) : WriteColorAttr<wk::ColorRGBA, false>(attr, value);
		}

		void WriteAttr(const std::string& name, const std::string& value, const std::string default_value = "")
		{
			if (value == default_value) return;

			m_node.append_attribute(name)
				.set_value(value);
		}

	public:
		XFLProp CreateProperty(DOM::PropTag prop)
		{
			return XFLProp(m_node, prop);
		}
		
	private:
		void InitializeNode(DOM::DOMElement& element, bool isRoot = false);

		template<typename T, bool write_alpha>
		void WriteColorAttr(DOM::Attribute& attr, const T& value)
		{
			std::stringstream ss{};
			auto write = [&ss](uint8_t value)
			{
				ss << std::setw(2) << std::setfill('0') << (int)value;
			};

			ss << "#" << std::hex;
			write(value.r);
			write(value.g);
			write(value.b);

			if constexpr(write_alpha)
			{
				write(value.a);
			}

			attr.set_value(ss.str());
		}

	private:
		DOM::Node m_node;
		wk::Ref<DOM::Document> m_root;
	};
}