#ifndef FRAMELAYER_HPP
#define FRAMELAYER_HPP

#include <IDataLink.hpp>
#include <Framework/Frame/IFrame.hpp>
#include <Framework/IReceive.hpp>
#include <Framework/TransmitBase.hpp>

namespace ModbusMaster
{
    class FrameLayer :
            public Framework::IReceive<Framework::Frame::IFrame>,
            public Framework::TransmitBase<std::vector<uint8_t>>
    {
    public:
        FrameLayer();

        bool Receive(Framework::Frame::IFrame &frame) override;
    };
} // Namespace ModbusMaster.

#endif // FRAMELAYER_HPP
