#pragma once

#include "PicObject.h"
#include "PicLayer.h"

#include <vector>
#include <optional>
#include "core/memory/ref.h"

namespace Animate::Library
{
	class DocumentPage;
}

namespace Animate::Pic
{
	struct LayerCopyData
	{
		Object::Childrens targets;
	};


	class Page : public Object
	{
	public:
		static inline LayerCopyData sCopyPasteLayerData;

	public:
		static wk::Ref<Page> Create(Library::DocumentPage& doc);

	public:
		virtual bool IsPicPage() const override { return true; };
		void SetOwner(Library::DocumentPage& doc);
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t /*index*/) const override;

	public:
		Layer& AddNewLayer(const String& name, bool is_folder, const std::optional<Layer>& parent = std::nullopt);
		void SetLayerWithNamingRules(Layer& layer, const String& name);
		void CopyLayers(size_t begin_index, size_t count = 1);
		size_t PasteLayers(size_t begin_index = -1);

	public:
		size_t LayersCount() const { return ChildrenCount(); }
		PicIterator<Layer> begin() { return PicIterator<Layer>::CreateBegin(*this); }
		PicIterator<Layer> end() { return PicIterator<Layer>::CreateEnd(*this); }
		Layer& operator [](size_t index) { return ChildAt<Layer>(index); }
	
	protected:
		Layer& AddLayer(bool a1, bool makeActive);
		Layer& AddFolder();

		virtual Object* CloneObject()
		{
			return new Page(*this);
		}

	private:
		Library::DocumentPage* m_ownerPage;
	};
}