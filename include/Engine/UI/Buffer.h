#pragma once
#include <type_traits>

namespace Engine::UI
{
    template <typename T>
    class Buffer
    {

    public:
        template <typename... Args>
        Buffer(Args&&... args)
            : value(std::forward<Args>(args)...)
            , buffer(value)
        {}

        Buffer(const T &value)
            : value(value)
            , buffer(value)
        {}

        Buffer(T &&value)
            : value(std::move(value))
            , buffer(value)
        {}

        Buffer(const Buffer &rhs)
            : value(rhs.value)
            , buffer(rhs.buffer)
        {}

        Buffer(Buffer &&rhs)
            : value(std::move(rhs.value))
            , buffer(std::move(rhs.buffer))
        {}

        Buffer &operator=(const T &rhs)
        {
            value = rhs;
            buffer = rhs;
            return *this;
        }

        Buffer &operator=(T &&rhs)
        {
            value = std::move(rhs);
            buffer = value;
            return *this;
        }

        Buffer &operator=(const Buffer &rhs)
        {
            value = rhs.value;
            buffer = rhs.buffer;
            return *this;
        }

        Buffer &operator=(Buffer &&rhs)
        {
            value = std::move(rhs.value);
            buffer = std::move(rhs.buffer);
            return *this;
        }

        ~Buffer() = default;

    public:
        operator T() const
        {
            return value;
        }

    public:
        T &GetBuffer() { return buffer; }
        const T &GetBuffer() const { return buffer; }
        T *const GetBufferPtr() { return &buffer; }
        void SetBuffer(const T &value) { buffer = value; }
        void SetBuffer(T &&value) { buffer = std::move(value); }

    public:
        bool IsValueDiffersFromBuffer() { return value != buffer; }
        void SetValueToBuffer() { value = buffer; }

    private:
        T value;
        T buffer;
    };
}