#pragma once

#include <optional>
#include <filesystem>

#include "Library/LibraryItem.h"

namespace Animate::Library
{
	class LibraryFolder : public LibraryItem
	{
	public:
		LibraryFolder(Document::SketchDocument& document, std::optional<std::u16string> name);

	public:
		virtual bool IsFolder() const override
		{
			return true;
		}

		virtual bool IsExpanded() const { return m_expanded; }
		virtual void SetExpanded(bool status) { m_expanded = status; }

#pragma region Object capabilities
		virtual bool CanBeParent() const override
		{
			return true;
		}
#pragma endregion

	public:
		virtual void WriteXFL(XFL::XFLWriter& writer) const;

	private:
		std::filesystem::path m_library_path;
		bool m_expanded = false;
	};
}