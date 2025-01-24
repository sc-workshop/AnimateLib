#pragma once

#include "core/generic/non_copyable.h"
#include "core/memory/ref.h"

#include "Library/LibraryItem.h"
#include "Library/Properties/LibraryItemID.h"

#include <list>
#include <string>
#include <functional>
#include <execution>

namespace Animate::Document
{
	template<typename T = Library::LibraryItem, typename P = Library::LibraryItem*>
	class LibraryItemsVector_t
	{
	public:
		using Reference = T&;
		using Pointer = T*;
		using Value = P;

	public:
		LibraryItemsVector_t() = default;

	public:
		void Reserve(size_t capacity)
		{
			m_items.reserve(capacity);
		}

		bool Contains(const std::u16string& name)
		{
			return Get(name) != nullptr;
		}

		Pointer Get(const std::u16string& name)
		{
			return Find(
				[&name](Value& item)
				{
					return item->GetLibraryName() == name;
				}
			);
		}

		Pointer Get(const Library::LibraryItemID& id)
		{
			return Find(
				[&id](Value& item)
				{
					return item->GetID() == id;
				}
			);
		}

		template<typename Cls, typename ... Args>
		Cls& Add(Args&&... args)
		{
			Cls* result = new Cls(args...);
			m_items.emplace_back(result);

			return *result;
		}

		template<typename ... Args>
		Value& AddInplace(Args&&... args)
		{
			return m_items.emplace_back(std::forward<Args>(args)...);
		}

		Pointer Find(std::function<bool(Value&)> cond)
		{
			auto it = std::find_if(std::execution::par_unseq, m_items.begin(), m_items.end(), cond);

			if (it != m_items.end())
			{
				return &(**it);
			}

			return nullptr;
		}

		const Reference At(size_t index) const
		{
			return *m_items.at(index);
		}

		Reference At(size_t index)
		{
			return *m_items.at(index);
		}

		size_t Length() const
		{
			return m_items.size();
		}

	private:
		std::vector<Value> m_items;
	};

	// List of items
	template<typename T>
	using LibraryItemsVector = LibraryItemsVector_t<T, wk::Unique<T>>;

	// List of references to items
	using LibraryReferenceVector = LibraryItemsVector_t<Library::LibraryItem, Library::LibraryItem*>;
}