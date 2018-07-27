#include "FrameLayer.hpp"

namespace ModbusMaster
{
    FrameLayer::FrameLayer()
    {}

    bool FrameLayer::Receive(Framework::Frame &frame)
    {
        auto bytes = frame.GetBytes();
        return Transmit(bytes);
    }
} // Namespace ModbusMaster.
