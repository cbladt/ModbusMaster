#include "FrameHeader.hpp"

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    FrameHeader::FrameHeader(uint8_t slaveId, FunctionCode functionCode) :
        _slaveId(slaveId),
        _functionCode(functionCode)
    {}

    FrameHeader::FrameHeader(uint8_t slaveId, uint8_t functionCode) :
        _slaveId(slaveId),
        _functionCode(static_cast<FunctionCode>(functionCode))
    {}

    uint8_t FrameHeader::GetSlaveId() const
    {
        return _slaveId;
    }

    FunctionCode FrameHeader::GetFunctionCode() const
    {
        return _functionCode;
    }
} // Namespace Frame.
} // Namespace Framework.
} // Namespace ModbusMaster.
