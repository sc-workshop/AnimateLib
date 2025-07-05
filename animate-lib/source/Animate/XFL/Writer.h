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
#include "core/string/string_converter.h"

#include "core/math/color_rgb.h"
#include "core/math/color_rgba.h"
#include "core/math/rect.h"

namespace Animate::DOM
{
	class DOMElement;
	class DOMItem;
	class DOMMediaItem;
	class Include;
}

namespace Animate::XFL
{
	class XFLWriter;
	using XFLProp = XFLWriter;

	class XFLWriter
	{
	public:
		XFLWriter(DOM::DOMElement& element);
		XFLWriter(DOM::Node node, DOM::DOMElement& element);
		XFLWriter(XFLWriter& node, DOM::DOMElement& element);
		XFLWriter(DOM::Node node, DOM::PropTag prop);

	public:
		void Save(const Path& path, IO::Stream& stream);

	public:
		template<
			typename T,
			typename std::enable_if_t<
			std::is_enum_v<T> ||
			std::is_arithmetic_v<T> ||
			std::is_pointer_v<T>
			, bool> = true>
		void WriteAttr(const std::string & name, const T & value, const T& default_value, const T& min, const T& max)
		{
			if (value == default_value) return;
			
			T finalValue = std::max<T>(std::min<T>(value, max), min);

			m_node.append_attribute(name)
				.set_value(finalValue);
		}

		template<
			typename T,
			typename std::enable_if_t<
			std::is_enum_v<T> ||
			std::is_arithmetic_v<T> ||
			std::is_pointer_v<T>
			, bool> = true>
		void WriteAttr(const std::string& name, const T& value, const T& default_value)
		{
			if (value == default_value) return;

			m_node.append_attribute(name)
					.set_value(value);
		}

		template<
			typename T,
			typename std::enable_if_t<
			std::is_enum_v<T> ||
			std::is_arithmetic_v<T> ||
			std::is_pointer_v<T>
			, bool> = true>
		void WriteAttr(const std::string & name, const T & value)
		{
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

		void WriteAttr(const std::string& name, const std::u16string& value, const std::u16string default_value = u"")
		{
			if (value == default_value) return;

			m_node.append_attribute(name)
				.set_value(pugi::as_utf8((const wchar_t*)value.data()));
		}

		void SetValue(const std::string& str)
		{
			m_node.set_value(str);
		}

		void SetValue(const std::u16string& str)
		{
			m_node.set_value(pugi::as_utf8((const wchar_t*)str.data()));
		}

	public:
		XFLProp CreateProperty(DOM::PropTag prop)
		{
			return XFLProp(m_node, prop);
		}

	public:
		static std::u16string MakePrefferedPath(const Path& path, bool is_symbol = false)
		{
			const std::u16string from = u"\\";
			const std::u16string to = u"/";

			std::u16string result = path.u16string();
			size_t startPos = 0;
			while ((startPos = result.find(from, startPos)) != std::u16string::npos) {
				result.replace(startPos, from.length(), to);
				startPos += to.length();
			}

			if (is_symbol)
			{
				result += u".xml";
			}

			return result;
		}
		
	private:
		void InitializeNode(DOM::DOMElement& element, bool isRoot = false);

		template<typename T, bool write_alpha>
		void WriteColorAttr(DOM::Attribute& attr, const T& value)
		{
			std::string result;
			if constexpr (write_alpha)
			{
				result = wk::StringConverter::ToHex(value.r, value.g, value.b, value.a);
			}
			else
			{
				result = wk::StringConverter::ToHex(value.r, value.g, value.b);
			}

			std::transform(result.begin(), result.end(), result.begin(),
				[](uint8_t c) { return (uint8_t)std::toupper(c); });

			
			attr.set_value(std::string("#") + result);
		}

	private:
		DOM::Node m_node;
		wk::Ref<DOM::Document> m_root;
	};
}