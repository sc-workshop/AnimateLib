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
		Layer& AddNewLayer(const String& name, bool is_folder = false, bool add_above = false, std::optional<std::reference_wrapper<Layer>> parent = std::nullopt);
		void SetLayerWithNamingRules(Layer& layer, const String& name);
		void CopyLayers(size_t begin_index, size_t count = 1);
		size_t PasteLayers(size_t begin_index = -1);
		void MoveLayer(Layer& layer, Layer& target, bool add_above = true);
		void MoveLayerInto(Layer& layer, Layer& target, bool add_above = true);

	public:
		// Access operators

		size_t LayersCount() const { return ChildrenCount(); }
		Iterator<Layer> begin() { return Iterator<Layer>::CreateBegin(*this); }
		Iterator<Layer> end() { return Iterator<Layer>::CreateEnd(*this); }
		ConstIterator<Layer> begin() const { return ConstIterator<Layer>::CreateBegin(*this); }
		ConstIterator<Layer> end() const { return ConstIterator<Layer>::CreateEnd(*this); }
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