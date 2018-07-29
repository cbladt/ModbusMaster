#ifndef IFRAME_HPP
#define IFRAME_HPP

#include <Framework/Frame/FrameHeader.hpp>

#include <cstdint>
#include <vector>

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    class IFrame
    {
    public:
        virtual ~IFrame() {}

        virtual const std::vector<uint8_t>& GetBytes() = 0;

        virtual FrameHeader GetFrameHeder() const = 0;
    };
} // Namespace Frame.
} // Namesaoce Framework.
} // Namesaoce ModbusMaster.

#endif // IFRAME_HPP
