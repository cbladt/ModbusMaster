#ifndef FRAME_HPP
#define FRAME_HPP

#include <cstdint>
#include <vector>

namespace ModbusMaster
{
namespace Framework
{
    class Frame
    {
    public:
        Frame();

        std::vector<uint8_t> GetBytes() const;
    };
} // Namespace Framework.
} // Namespace ModbusMaster.

#endif // FRAME_HPP
