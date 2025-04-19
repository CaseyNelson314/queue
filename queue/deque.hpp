#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <numeric>
#include <iterator>

template <typename T>
class deque
{
    struct chunk
    {
        static constexpr size_t capacity = 3;

        struct {
            T value;
            bool is_empty = true;
        } values[capacity];

        size_t size;

        bool full() const noexcept
        {
            return size >= capacity;
        }

        void push_back(const T& value)
        {
            values[size++] = { value, false };
        }

        void push_back(T&& value)
        {
            values[size++] = { std::move(value), false };
        }
    };

    std::vector<std::unique_ptr<chunk>> storage;

public:

    struct iterator;
    struct const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    deque() = default;

    deque(std::initializer_list<T> init)
    {
        for (auto&& e : init)
        {
            push(std::move(e));
        }
    }

    void push(const T& value)
    {
        if (storage.empty() or storage.back()->full())
        {
            storage.push_back(std::make_unique<chunk>());
        }

        storage.back()->push_back(value);
    }

    size_t size() const noexcept
    {
        if (storage.empty())
        {
            return 0;
        }
        else
        {
            return (storage.size() - 1) * chunk::capacity + storage.back()->size;
        }
    }

    bool empty() const noexcept
    {
        return size() == 0;
    }

    T& operator[](size_t i)
    {
        const auto chunk_index = i / chunk::capacity;
        const auto data_index = i % chunk::capacity;

        return storage[chunk_index]->values[data_index].value;
    }

    T& at(size_t i)
    {
        if (i >= size())
            throw std::out_of_range("deque out of range");
        else
            return (*this)[i];
    }

    const T& operator[](size_t i) const
    {
        const auto chunk_index = i / chunk::capacity;
        const auto data_index = i % chunk::capacity;

        return storage[chunk_index]->values[data_index].value;
    }

    const T& at(size_t i) const
    {
        if (i >= size())
            throw std::out_of_range("deque out of range");
        else
            return (*this)[i];
    }

    struct iterator
    {
        deque* self;

        size_t i;

        iterator& operator++()
        {
            ++i;
            return *this;
        }

        T& operator*()
        {
            return self->operator[](i);
        }

        friend bool operator!=(const iterator& l, const iterator& r)
        {
            return l.i != r.i;
        }
    };

    struct const_iterator
    {
        const deque* self;

        size_t i;

        const_iterator& operator++()
        {
            ++i;
            return *this;
        }

        const T& operator*() const
        {
            return self->operator[](i);
        }

        friend bool operator!=(const const_iterator& l, const const_iterator& r)
        {
            return l.i != r.i;
        }
    };

    iterator begin()
    {
        return { this, 0 };
    }
    const_iterator begin() const
    {
        return cbegin();
    }
    const_iterator cbegin() const
    {
        return { this, 0 };
    }

    iterator end()
    {
        return { this, size() };
    }
    const_iterator end() const
    {
        return cend();
    }
    const_iterator cend() const
    {
        return { this, size() };
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator{ begin() };
    }
    const_reverse_iterator rbegin() const
    {
        return crbegin();
    }
    const_reverse_iterator crbegin() const
    {
        return reverse_iterator{ begin() };
    }

    reverse_iterator rend()
    {
        return reverse_iterator{ end() };
    }
    const_reverse_iterator rend() const
    {
        return crend();
    }
    const_reverse_iterator crend() const
    {
        return reverse_iterator{ end() };
    }

};
