#include "ReadRegistersFrame.hpp"

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    ReadRegistersFrame::ReadRegistersFrame(FrameHeader header, uint16_t startAddress, uint16_t count) :
        _header(header),
        _startAddress(startAddress),
        _count(count)
    {
        _bytes.push_back(_header.GetSlaveId());
        _bytes.push_back(static_cast<uint8_t>(_header.GetFunctionCode()));
        _bytes.push_back(reinterpret_cast<uint8_t*>(&_startAddress)[1]);
        _bytes.push_back(reinterpret_cast<uint8_t*>(&_startAddress)[0]);
        _bytes.push_back(reinterpret_cast<uint8_t*>(&_count)[1]);
        _bytes.push_back(reinterpret_cast<uint8_t*>(&_count)[0]);
    }

    const std::vector<uint8_t>& ReadRegistersFrame::GetBytes()
    {
        return _bytes;
    }

    FrameHeader ReadRegistersFrame::GetFrameHeder() const
    {
        return _header;
    }

    uint16_t ReadRegistersFrame::GetStartAddress() const
    {
        return _startAddress;
    }

    uint16_t ReadRegistersFrame::GetCount() const
    {
        return _count;
    }
} // Namespace Frame.
} // Namespace Framework.
} // Namesapce ModbusMaster.
