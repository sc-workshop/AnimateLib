#pragma once

#include "Properties/LinkageProps.h"
#include "Properties/LibraryItemID.h"

#include "Animate/XFL/Writer.h"
#include "Animate/XFL/File.h"

#include "core/generic/non_copyable.h"
#include "core/generic/non_movable.h"

#include <optional>
#include <string>
#include <time.h>
#include <mutex>
#include <algorithm>

namespace Animate::Document
{
	class SketchDocument;
}

namespace Animate::Library
{
	class LibraryItem
	{
	public:
		LibraryItem(Document::SketchDocument& document, std::optional<std::u16string> name = std::nullopt);

	public:
#pragma region Item types
		virtual bool IsFolder() const
		{
			return false;
		}

		virtual bool IsDocumentPage() const
		{
			return false;
		}

		virtual bool IsFont() const
		{
			return false;
		}

		virtual bool IsMedia() const
		{
			return false;
		}
#pragma endregion

#pragma region Object capabilities
		virtual bool CanBeParent() const
		{
			return false;
		}

		virtual bool IsPlayable() const
		{
			return false;
		}

		virtual bool IsEditable() const
		{
			return false;
		}

		virtual bool IsUpdateable() const
		{
			return false;
		}

		virtual bool IsDuplicatable() const
		{
			return false;
		}

		virtual bool IsPreviewable()
		{
			return false;
		}

#pragma endregion

#pragma region Virtual change callbacks
		virtual void OnParentChange();

#pragma endregion

		virtual LinkageProps& GetLinkageProps()
		{
			return m_linkage;
		}

		virtual void SetID(const LibraryItemID& id) { m_item_id = id; };
		virtual void SetParentID(const LibraryItemID& id) { m_parent_id = id; OnParentChange(); };

		virtual const LibraryItemID& GetID() const { return m_item_id; };
		virtual const LibraryItemID& GetParentID() const { return m_parent_id; };

		const bool HasNoParent() const { return m_parent_id == LibraryItemID::NoParent; };

		virtual void SetItemName(const std::u16string& name);
		virtual std::u16string GetItemName() const;
		virtual Path GetItemPath() const;

		virtual time_t GetModDateForLibrary() const;
		virtual void SetModDateForLibrary(time_t);

		virtual void WriteXFL(XFL::XFLFile& /*file*/, XFL::XFLWriter& /*writer*/) const {};
		bool SetParent(const LibraryItem& parent);

		Document::SketchDocument& GetSketchDoc();

	protected:
		void SetItemPathDirty() const;
		bool IsItemPathDirty() const;

		void ConstructLibraryPath() const;

		void InitializeDOMItem(DOM::DOMItem& item) const;

	protected:
		mutable std::mutex m_mutex;
		mutable Path m_item_path;
		std::u16string m_item_name;

		LibraryItemID m_parent_id = LibraryItemID::NoParent;
		mutable LibraryItemID m_item_id = LibraryItemID::NullItemID;

		LinkageProps m_linkage;
		Document::SketchDocument& m_document;

	private:
		mutable bool m_item_path_dirty = true;
	};
}