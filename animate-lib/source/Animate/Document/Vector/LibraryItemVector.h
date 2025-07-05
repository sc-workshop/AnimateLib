#pragma once

#include "core/generic/non_copyable.h"
#include "core/memory/ref.h"

#include "Animate/Library/LibraryItem.h"
#include "Animate/Library/Properties/LibraryItemID.h"

#include <list>
#include <string>
#include <functional>
#include <execution>

namespace Animate::Document
{
	/// <summary>
	/// Helper class that in essential is std::vector but with some enhancements in this specific case
	/// </summary>
	/// <typeparam name="T">Base type</typeparam>
	/// <typeparam name="P">Pointer type</typeparam>
	template<typename T = Library::LibraryItem, typename P = Library::LibraryItem*>
	class LibraryItemsVector_t
	{
	public:
		using Reference = T&;
		using Pointer = T*;
		using Value = P;

		template<typename T>
		using Container = std::vector<T>; // TODO: replace for std::list ?

	public:
		LibraryItemsVector_t() = default;

	public:
		void Reserve(size_t capacity)
		{
			m_symbols.reserve(capacity);
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
					return item->GetItemName() == name;
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
			m_symbols.emplace_back(result);

			return *result;
		}

		template<typename ... Args>
		Value& AddInplace(Args&&... args)
		{
			return m_symbols.emplace_back(std::forward<Args>(args)...);
		}

		Pointer Find(std::function<bool(Value&)> cond)
		{
			auto it = std::find_if(std::execution::par_unseq, m_symbols.begin(), m_symbols.end(), cond);

			if (it != m_symbols.end())
			{
				return &(**it);
			}

			return nullptr;
		}

		size_t Length() const
		{
			return m_symbols.size();
		}

		void Move(size_t from, size_t to)
		{
			if (from >= m_symbols.size() || to >= m_symbols.size())
			{
				return; // Out of bounds
			}
			if (from == to)
			{
				return; // No need to move
			}

			auto item = std::move(m_symbols[from]);
			m_symbols.erase(m_symbols.begin() + from);
			m_symbols.insert(m_symbols.begin() + to, std::move(item));
		}

	public:
		// Access operators

		const Reference At(size_t index) const
		{
			return *m_symbols.at(index);
		}

		Reference At(size_t index)
		{
			return *m_symbols.at(index);
		}

		Reference operator [](size_t index)
		{
			return At(index);
		}

		const Reference operator [](size_t index) const
		{
			return At(index);
		}

		typename Container<Value>::iterator begin() { return m_symbols.begin(); }
		typename Container<Value>::iterator end() { return m_symbols.end(); }

		typename Container<Value>::const_iterator begin() const { return m_symbols.cbegin(); }
		typename Container<Value>::const_iterator end() const { return m_symbols.cend(); }

	private:
		Container<Value> m_symbols;
	};

	// List of items
	template<typename T>
	using LibraryItemsVector = LibraryItemsVector_t<T, wk::Ref<T>>;

	// List of references to items
	using LibraryReferenceVector = LibraryItemsVector_t<Library::LibraryItem, Library::LibraryItem*>;
}