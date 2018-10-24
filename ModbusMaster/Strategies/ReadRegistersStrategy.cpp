#include "ReadRegistersStrategy.hpp"

#include <cstddef>

static const size_t MaxParamsPerRequest = 127 ;

namespace ModbusMaster
{
namespace Strategies
{
    ReadRegistersStratety::ReadRegistersStratety(IReadRegistersCallback& callback) :
        _callback(callback),
        _isExpecting(false),
        _lastTransmittedFrameHeader(0,0),
        _lastTransmittedRegisterCount(0),
        _lastTransmittedStartAddress(0)
    {}

    void ReadRegistersStratety::Service(uint64_t)
    {}

    bool ReadRegistersStratety::Receive(RequestModel &data)
    {        
        // Ensure not too many params.
        if (data.GetCount() > MaxParamsPerRequest) return false;

        auto start = data.GetStartAddress();

        // Create frame.
        _lastTransmittedFrameHeader = Framework::Frame::FrameHeader(data.GetDevice(), data.GetFunctionCode());
        _lastTransmittedRegisterCount = data.GetCount();
        Framework::Frame::ReadRegistersFrame frame(_lastTransmittedFrameHeader, start, _lastTransmittedRegisterCount);

        // Create FrameRequestModel.
        uint8_t expectedBytes = (data.GetCount() * 2) + 1; // Total Size of all parameters + Datalength.
        Framework::Frame::FrameRequestModel frameRequestModel(frame, *this, expectedBytes);

        _isExpecting = true;
        return Transmit(frameRequestModel);
    }

    bool ReadRegistersStratety::Receive(Framework::Frame::FrameContent &data)
    {
        if (!_isExpecting) return false;
        if (data.GetIsEmpty()) return false;

        // First byte is the amount of bytes to follow. Assert that.
        if (data.At(0) != (data.GetSize() - 1)) return false;
        if ((data.GetSize() - 1) % 2 != 0) return false;

        auto values = reinterpret_cast<const uint16_t*>(&data.At(1));
        _callback.ReadRegistersCallback(_lastTransmittedFrameHeader.GetFunctionCode(), _lastTransmittedStartAddress, _lastTransmittedRegisterCount, values);

        return true;
    }     

} // Namespace Strategies.
} // Namespace ModbusMaster.
