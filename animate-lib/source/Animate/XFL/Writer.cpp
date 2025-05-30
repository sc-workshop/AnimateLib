#include "Writer.h"
#include "DOM/DOMElement.h"
#include "DOM/Items/DOMItem.h"
#include "DOM/Items/DOMMediaItem.h"
#include "DOM/Document/Include.h"
#include "DOM/Items/DOMBitmapItem.h"

namespace Animate::XFL
{
	struct XMLWriter : pugi::xml_writer
	{
		IO::Stream& stream;

		XMLWriter(IO::Stream& _stream, const Path& path) : stream(_stream)
		{ 
			if (!stream.OpenFile(path))
			{
				throw wk::Exception("Failed to open file for writing: " + path.string());
			}
		}

		virtual ~XMLWriter()
		{
			stream.CloseFile();
		}

		virtual void write(const void* data, size_t size)
		{
			if (stream.WriteFile(data, size) != size)
			{
				throw wk::Exception("Failed to write data to file");
			}
		}
	};

	XFLWriter::XFLWriter(DOM::DOMElement& element)
	{
		m_root = wk::CreateRef<DOM::Document>();
		m_node = m_root->append_child();
		InitializeNode(element, true);
	}

	XFLWriter::XFLWriter(DOM::Node node, DOM::DOMElement& element)
	{
		m_node = node.append_child();
		InitializeNode(element);
	}

	XFLWriter::XFLWriter(XFLWriter& node, DOM::DOMElement& element)
	{
		m_node = node.m_node.append_child();
		InitializeNode(element);
	}

	XFLWriter::XFLWriter(DOM::Node node, DOM::PropTag prop)
	{
		m_node = node.append_child();
		m_node.set_name(DOM::GetPropName(prop));
	}

	void XFLWriter::InitializeNode(DOM::DOMElement& element, bool isRoot)
	{
		// Declaring namespaces
		if (isRoot)
		{
			m_node.append_attribute("xmlns:xsi")
				.set_value("http://www.w3.org/2001/XMLSchema-instance");

			m_node.append_attribute("xmlns")
				.set_value("http://ns.adobe.com/xfl/2008/");
		}

		const char* tag = DOM::GetElementTag(element.GetTag());
		m_node.set_name(tag);
		element.SetAttributes(*this);
	}

	void XFLWriter::Save(const Path& path, IO::Stream& stream)
	{
		if (!m_root)
		{
			throw wk::Exception("XML Root does not initialized or corrupted");
		}

		XMLWriter writer(stream, path);
		m_root->print(writer);
	}
}