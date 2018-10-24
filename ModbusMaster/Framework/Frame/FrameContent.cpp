#include "FrameContent.hpp"

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    FrameContent::FrameContent() :
        _index(0)
    {}

    bool FrameContent::Push(FrameContent::Type value)
    {
        _index++;

        if (_index >= Size)
        {
            return false;
        }

        _container.at(_index) = value;

        return true;
    }

    void FrameContent::Clear() noexcept
    {
        _index = 0;
    }

    bool FrameContent::GetIsEmpty() const noexcept
    {
        return _index > 0;
    }

    const FrameContent::Type& FrameContent::At(size_t index) const
    {
        return _container.at(index);
    }

    size_t FrameContent::GetSize() const noexcept
    {
        return _index + 1;
    }
} // Namespace Frame.
} // Namespace Framework.
} // Namespace ModbusMaster.
