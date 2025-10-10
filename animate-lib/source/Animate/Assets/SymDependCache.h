#pragma once

#include <map>
#include <set>
#include "Animate/Library/LibraryItem.h"
#include "Animate/Library/LibraryItem/DocumentPage.h"

namespace Animate {
	struct SymDependInfo {
		std::mutex mt;
		std::set<Library::LibraryItem const *> references;
	};

	class SymDependCache
	{
	public:
		operator bool() const { return !m_symbols.empty(); }

		void SetCurrentDocPage(const Library::LibraryItem* item);
		SymDependInfo* AddSymbol(const Library::LibraryItem&);
		void AddSymbolReference(const Library::LibraryItem&);
		bool WriteXFL(XFL::XFLFile& file) const;

	private:
		static thread_local inline Library::LibraryItem const * s_docPage = nullptr;
		std::map<Library::LibraryItem const*, SymDependInfo> m_symbols;
		std::mutex m_mut;
	};
}
