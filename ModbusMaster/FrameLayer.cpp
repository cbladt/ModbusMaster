#include "FrameLayer.hpp"

namespace ModbusMaster
{
    FrameLayer::FrameLayer()
    {}

    bool FrameLayer::Receive(Framework::Frame::IFrame &frame)
    {
        auto bytes = frame.GetBytes();
        return Transmit(bytes);
    }
} // Namespace ModbusMaster.
