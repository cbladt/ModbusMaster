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
        _lastTransmittedFrame(Framework::Frame::FrameHeader(0,0), 0, 0)
    {}

    void ReadRegistersStratety::Service(uint64_t)
    {

    }

    bool ReadRegistersStratety::Receive(RequestModel &data)
    {        
        // Ensure not too many params.
        if (data.GetCount() > MaxParamsPerRequest) return false;

        auto start = data.GetStartAddress();

        // Create frame.
        Framework::Frame::FrameHeader header(data.GetDevice(), data.GetFunctionCode());
        _lastTransmittedFrame = Framework::Frame::ReadRegistersFrame(header, start, data.GetCount());

        // Create FrameRequestModel.
        uint8_t expectedBytes = (data.GetCount() * 2) + 1; // Total Size of all parameters + Datalength.
        Framework::Frame::FrameRequestModel frameRequestModel(_lastTransmittedFrame, *this, expectedBytes);

        _isExpecting = true;
        return Transmit(frameRequestModel);
    }

    bool ReadRegistersStratety::Receive(std::vector<uint8_t> &data)
    {
        if (!_isExpecting) return false;
        if (data.empty()) return false;

        // First byte is the amount of bytes to follow. Assert that.
        if (data[0] != (data.size() - 1)) return false;
        if ((data.size() - 1) % 2 != 0) return false;

        auto values = reinterpret_cast<uint16_t*>(&data[1]);
        _callback.ReadRegistersCallback(_lastTransmittedFrame.GetFrameHeder().GetFunctionCode(), _lastTransmittedFrame.GetStartAddress(), _lastTransmittedFrame.GetCount(), values);

        return true;
    }

} // Namespace Strategies.
} // Namespace ModbusMaster.
