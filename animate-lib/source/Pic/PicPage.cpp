#include "PicPage.h"

namespace Animate::Pic
{
	wk::Ref<Page> Page::Create(Library::DocumentPage& doc)
	{
		auto object = wk::Ref<Page>();
		object->SetOwner(doc);
		return object;
	}

	void Page::SetOwner(Library::DocumentPage& doc)
	{
		m_owner = &doc;
	}

	void Page::WriteXFL(XFL::XFLWriter& writer) const
	{
		auto layers = writer.CreateProperty(DOM::PropTag::Layers);

		for (size_t i = 0; ChildrenCount() > i; i++)
		{
			const auto& layer = ChildAt<Layer>(i);
			assert(layer.IsPicLayer() != true);

			layer.WriteXFL(layers);

		}
	}

	Layer& Page::AddNewLayer(const String& name, bool is_folder, const std::optional<Layer>& parent)
	{
		Layer& layer = is_folder ? AddFolder() : AddLayer(false, false);

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

