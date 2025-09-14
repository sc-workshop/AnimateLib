#pragma once

#include <iterator>

namespace Animate::Pic
{
    class Object;

    template<typename T, typename PT>
    class PicIterator {
    public:
        static PicIterator<T, PT> CreateBegin(PT& parent)
        {
            return PicIterator<T, PT>(parent, 0);
        }

        static PicIterator<T, PT> CreateEnd(PT& parent)
        {
            size_t children_count = parent.ChildrenCount();
            return PicIterator<T, PT>(parent, children_count);
        }

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        PicIterator(PT& parent, size_t index)
            : parent(parent), position(index) {
        }

        reference operator*() const { return parent.template ChildAt<T>(position); }
        pointer operator->() const { return &this->operator*(); }

        PicIterator& operator++() { ++position; return *this; }
        PicIterator operator++(int) { auto tmp = *this; ++(*this); return tmp; }

        PicIterator& operator--() { --position; return *this; }
        PicIterator operator--(int) { auto tmp = *this; --(*this); return tmp; }

        PicIterator& operator+=(difference_type n) { position += n; return *this; }
        PicIterator& operator-=(difference_type n) { position -= n; return *this; }

        PicIterator operator+(difference_type n) const { return PicIterator(parent, position + n); }
        PicIterator operator-(difference_type n) const { return PicIterator(parent, position - n); }

        difference_type operator-(const PicIterator& other) const {
            return static_cast<difference_type>(position) - static_cast<difference_type>(other.position);
        }

        bool operator==(const PicIterator& other) const { return position == other.position && std::addressof(parent) == std::addressof(other.parent); }
        bool operator!=(const PicIterator& other) const { return !(*this == other); }
        bool operator<(const PicIterator& other) const { return position < other.position; }
        bool operator<=(const PicIterator& other) const { return position <= other.position; }
        bool operator>(const PicIterator& other) const { return position > other.position; }
        bool operator>=(const PicIterator& other) const { return position >= other.position; }

        reference operator[](difference_type n) const { return parent.ChildAt(position + n); }

    private:
        PT& parent;
        size_t position;
    };

    template<typename T>
	using Iterator = PicIterator<T, Object>;

    template<typename T>
    using ConstIterator = PicIterator<const T, const Object>;
}