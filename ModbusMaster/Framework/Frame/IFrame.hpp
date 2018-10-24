#ifndef IFRAME_HPP
#define IFRAME_HPP

#include <Framework/Frame/FrameHeader.hpp>
#include <Framework/Frame/FrameContent.hpp>

#include <cstdint>

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    class IFrame
    {
    public:
        virtual ~IFrame() = default;
        virtual FrameContent& GetBytes() = 0;
        virtual FrameHeader GetFrameHeder() const = 0;
    };
} // Namespace Frame.
} // Namesaoce Framework.
} // Namesaoce ModbusMaster.

#endif // IFRAME_HPP
