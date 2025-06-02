#include "PicPage.h"

#include "Animate/Document/SketchDocument.h"

namespace Animate::Pic
{
	wk::Ref<Page> Page::Create(Library::DocumentPage& doc)
	{
		auto object = wk::CreateRef<Page>();
		object->SetOwner(doc);
		return object;
	}

	void Page::SetOwner(Library::DocumentPage& doc)
	{
		m_ownerPage = &doc;
		Object::SetOwner(doc.GetSketchDoc());
	}

	void Page::WriteXFL(XFL::XFLWriter& writer, uint32_t /*index*/) const
	{
		uint32_t index = 0;
		for (const auto& layer : *this)
		{
			layer.WriteXFL(writer, index++);
		}
	}

	Layer& Page::AddNewLayer(const String& name, bool is_folder, bool add_above, std::optional<std::reference_wrapper<Layer>> parent)
	{
		Layer& layer = is_folder ? AddFolder() : AddLayer(false, false);

		if (parent)
		{
			if (layer.IsCameraLayer())
			{

			}
			else
			{
				MoveLayer(layer, parent.value(), add_above);
			}
		}

		if (!name.empty())
		{
			SetLayerWithNamingRules(layer, name);
		}

		return layer;
	}

	void Page::SetLayerWithNamingRules(Layer& layer, const String& name)
	{
		layer.SetName(name);
		// TODO: lookup tables, rule applying, etc
	}

	void Page::CopyLayers(size_t begin_index, size_t count)
	{
		if (begin_index >= ChildrenCount()) return;
		if (begin_index + count > ChildrenCount())
		{
			count = ChildrenCount() - begin_index;
		}

		for (size_t i = begin_index; begin_index + count > i; i++)
		{
			sCopyPasteLayerData.targets.push_back(m_childrens[i]);
		}
	}

	size_t Page::PasteLayers(size_t begin_index)
	{
		if (begin_index == -1)
		{
			begin_index = 0;
		}

		size_t result = begin_index;
		for (auto& layer : sCopyPasteLayerData.targets)
		{
			AddChildAt(begin_index++, layer->Clone());
		}
		sCopyPasteLayerData.targets.clear();

		return result;
	}

	void Page::MoveLayer(Layer& source, Layer& destination, bool add_above)
	{
		size_t destination_index = 0;
		assert(GetChildrenIndex(destination, destination_index));

		size_t source_index = 0;
		assert(GetChildrenIndex(source, source_index));
		
		MoveChildrens(source_index, add_above ? destination_index : ++destination_index);
	}

	Layer& Page::AddLayer(bool /*a1*/, bool /*makeActive*/)
	{
		Layer& layer = AddChild<Layer>();
		layer.SetOwner(*this);
		String name = "Layer " + std::to_string(ChildrenCount());
		layer.Initialize(name);

		return layer;
	}

	Layer& Page::AddFolder()
	{
		Layer& layer = AddChild<Layer>();
		layer.SetOwner(*this);
		String name = "Folder " + std::to_string(ChildrenCount());
		layer.Initialize(name);
		layer.SetFolder();

		return layer;
	}
}

