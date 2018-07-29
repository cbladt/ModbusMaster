#ifndef FRAMELAYER_HPP
#define FRAMELAYER_HPP

#include <IDataLink.hpp>
#include <Framework/Frame/FrameRequestModel.hpp>
#include <Framework/IReceive.hpp>
#include <Framework/TransmitBase.hpp>

namespace ModbusMaster
{
    class FrameLayer :           
            public Framework::IReceive<std::vector<uint8_t>>,
            public Framework::IReceive<Framework::Frame::FrameRequestModel>,
            public Framework::TransmitBase<std::vector<uint8_t>>
    {
    public:
        FrameLayer();

        bool Receive(Framework::Frame::FrameRequestModel &frameRequestModel) override;
        bool Receive(std::vector<uint8_t>& byte) override;

    private:
        Framework::Frame::FrameHeader _expectedHeader;
        size_t _expectedDataBytesRemaining;
        std::vector<uint8_t> _receivedBytes;
        uint16_t _receivedCrc;

        enum class ReceiveState
        {
            Idle,
            SlaveId,
            FunctionCode,
            Data,
            Crc1,
            Crc2,
            Done
        };
        ReceiveState _receiveState;

        bool HandleByte(uint8_t byte);
        void PrepareReceive(Framework::Frame::FrameHeader header, size_t dataBytes);
        bool VerifyCrc();
        void Reset();
    };
} // Namespace ModbusMaster.

#endif // FRAMELAYER_HPP
