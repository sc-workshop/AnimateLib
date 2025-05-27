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
	class Page : public Object
	{
	public:
		static wk::Ref<Page> Create(Library::DocumentPage& doc);

	public:
		virtual bool IsPicPage() const override { return true; };
		void SetOwner(Library::DocumentPage& doc);
		virtual void WriteXFL(XFL::XFLWriter& writer, uint32_t /*index*/) const override;

	public:
		Layer& AddNewLayer(const String& name, bool is_folder, const std::optional<Layer>& parent = std::nullopt);
		void SetLayerWithNamingRules(Layer& layer, const String& name);

	public:
		size_t LayersCount() const { return ChildrenCount(); }
		PicIterator<Layer> begin() { return PicIterator<Layer>::CreateBegin(*this); }
		PicIterator<Layer> end() { return PicIterator<Layer>::CreateEnd(*this); }
	
	protected:
		Layer& AddLayer(bool a1, bool makeActive);
		Layer& AddFolder();

	private:
		Library::DocumentPage* m_ownerPage;
	};
}