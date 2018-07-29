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
        // Ensure not empty.
        if (data.GetParameters().empty()) return false;

        // Ensure not too many params.
        if (data.GetParameters().size() > MaxParamsPerRequest) return false;

        auto start = data.GetParameters().front().GetAddress();
        auto count = static_cast<uint16_t>(data.GetParameters().size());

        Framework::Frame::FrameHeader header(data.GetDevice(), data.GetFunctionCode());

        Framework::Frame::ReadRegistersFrame frame(header, start, count);

        return Transmit(frame);
    }
} // Namespace Strategies.
} // Namespace ModbusMaster.
