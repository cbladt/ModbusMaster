#ifndef FRAMECONTENT_HPP
#define FRAMECONTENT_HPP

#include <array>

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    class FrameContent
    {
    private:
        enum { Size = 256 };
        using Type = uint8_t;

    public:
        FrameContent();
        ~FrameContent() = default;

        const Type* Data() const noexcept;

        const Type& At(size_t index) const;

        bool Push(Type value);

        void Clear() noexcept;

        bool GetIsEmpty() const noexcept;

        size_t GetSize() const noexcept;

        auto begin() const { return _container.cbegin(); }
        auto end() const { return _container.cbegin() + _index; }

    private:
        std::array<Type, Size> _container;
        size_t _index;

        FrameContent(const FrameContent&) = delete;
        const FrameContent& operator=(const FrameContent&) = delete;
    };
} // Namespace Frame.
} // Namespace Framework.
} // Namespace ModbusMaster.
#endif // FRAMECONTENT_HPP
