#include "SymDependCache.h"

namespace Animate {
	void SymDependCache::SetCurrentDocPage(const Library::LibraryItem* item)
	{
		// s_docPage is thread_local, so storing it is inherently thread-safe.
		s_docPage = item;

		// Make sure the page itself is registered in m_symbols under the shared
		// lock so that AddSymbolReference() can find it later from any thread.
		if (item)
			AddSymbol(*item);
	}

	SymDependInfo* SymDependCache::AddSymbol(const Library::LibraryItem& item)
	{
		// Every access to m_symbols must be done while holding m_mut: the cache
		// is mutated concurrently from the parallel symbol writer pool in
		// SketchDocument::WriteXFLSymbols(), and std::map provides no
		// concurrent reader/writer guarantees.
		std::lock_guard guard(m_mut);
		auto [it, isNew] = m_symbols.try_emplace((Library::LibraryItem*)&item);
		return &(it->second);
	}

	void SymDependCache::AddSymbolReference(const Library::LibraryItem& item)
	{
		SymDependInfo* node = nullptr;
		Library::LibraryItem const * referenced = (Library::LibraryItem const *)&item;

		// Lookup of both the referenced item and the current thread's parent
		// page (s_docPage) must share the lock with try_emplace, otherwise we
		// get a data race on the red-black tree of std::map.
		{
			std::lock_guard guard(m_mut);
			m_symbols.try_emplace(referenced);

			auto parent = m_symbols.find(s_docPage);
			if (parent == m_symbols.end())
				return; // The parent page was never registered - shouldn't happen
			node = &parent->second;
		}

		// Updating the reference set is protected per-symbol, allowing real
		// parallelism for symbols that belong to different parents.
		std::lock_guard<std::mutex> guard(node->mt);
		node->references.insert(referenced);
	}

	bool SymDependCache::WriteXFL(XFL::XFLFile& file) const
	{
		XFL::XflIoFile stream;
		stream.write_unsigned_int(103); // Magic number

		{
			struct SysTime16 { uint16_t year, month, wday, day, hour, minute, second, msec; } st{};
			auto now = std::chrono::system_clock::now();
			std::time_t tt = std::chrono::system_clock::to_time_t(now);
			tm local_tm;
#if defined(_WIN32)
			localtime_s(&local_tm, &tt);
#else
			localtime_r(&tt, &local_tm);
#endif
			st.year = static_cast<uint16_t>(local_tm.tm_year + 1900);
			st.month = static_cast<uint16_t>(local_tm.tm_mon + 1);
			st.wday = static_cast<uint16_t>(local_tm.tm_wday);
			st.day = static_cast<uint16_t>(local_tm.tm_mday);
			st.hour = static_cast<uint16_t>(local_tm.tm_hour);
			st.minute = static_cast<uint16_t>(local_tm.tm_min);
			st.second = static_cast<uint16_t>(local_tm.tm_sec);
			st.msec = 0;

			stream.write(&st, sizeof(st));
		}

		stream.write_unsigned_int((uint32_t)m_symbols.size());
		for (const auto& [symbol, info] : m_symbols) {
			auto path = symbol->GetItemPath().string();
			uint16_t pathLen = (uint16_t)path.length() + 1;

			stream.write_unsigned_short(pathLen);
			stream.write(path.c_str(), pathLen);
		}

		{
			stream.write_unsigned_int(44478);
			for (const auto& [symbol, info] : m_symbols) {
				stream.write_unsigned_int((uint32_t)info.references.size());
				for (auto ref : info.references) {
					size_t idx = std::distance(m_symbols.begin(), m_symbols.find(ref));
					stream.write_unsigned_int((uint32_t)idx);
				}
			}
		}

		file.SaveBinary("SymDepend.cache", stream);
		return true;
	}
}