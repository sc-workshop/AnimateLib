#pragma once

#include <iterator>

namespace Animate::Pic
{
    class Object;

    template<typename T>
    class PicIterator {
    public:
        static PicIterator<T> CreateBegin(Object& parent)
        {
            return PicIterator<T>(parent, 0);
        }

        static PicIterator<T> CreateEnd(Object& parent)
        {
            return PicIterator(parent, parent.ChildrenCount() - 1);
        }

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        PicIterator(Object& parent, size_t index)
            : parent(parent), position(index) {
        }

        reference operator*() const { return parent.ChildAt<T>(position); }
        pointer operator->() const { return &parent.ChildAt<T>(position); }

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
        Object& parent;
        size_t position;
    };
}