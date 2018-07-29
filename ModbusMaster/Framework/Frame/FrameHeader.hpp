#ifndef FRAMEHEADER_HPP
#define FRAMEHEADER_HPP

#include <Framework/FunctionCode.hpp>

#include <cstdint>

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    class FrameHeader
    {
    public:
        FrameHeader(uint8_t slaveId, FunctionCode functionCode);
        FrameHeader(uint8_t slaveId, uint8_t functionCode);

        uint8_t GetSlaveId() const;
        FunctionCode GetFunctionCode() const;

    private:
        uint8_t _slaveId;
        FunctionCode _functionCode;
    };
} // Namespace Frame.
} // Namespace Framework.
} // Namespace ModbusMaster.

#endif // FRAMEHEADER_HPP
