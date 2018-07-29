#include "ReadRegistersStrategy.hpp"

#include <Framework/Frame/ReadRegistersFrame.hpp>

#include <cstddef>

static const size_t MaxParamsPerRequest = 127 ;

namespace ModbusMaster
{
namespace Strategies
{
    ReadRegistersStratety::ReadRegistersStratety()
    {}

    bool ReadRegistersStratety::Receive(RequestModel &data)
    {        
        // Ensure not too many params.
        if (data.GetCount() > MaxParamsPerRequest) return false;

        auto start = data.GetStartAddress();

        // Create frame.
        Framework::Frame::FrameHeader header(data.GetDevice(), data.GetFunctionCode());
        Framework::Frame::ReadRegistersFrame frame(header, start, data.GetCount());

        // Create FrameRequestModel.
        uint8_t expectedBytes = (data.GetCount() * 2) + 1; // Total Size of all parameters + Datalength.
        Framework::Frame::FrameRequestModel frameRequestModel(frame, expectedBytes);

        return Transmit(frameRequestModel);
    }
} // Namespace Strategies.
} // Namespace ModbusMaster.
