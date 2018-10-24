#ifndef FRAMELAYER_HPP
#define FRAMELAYER_HPP

#include <IDataLink.hpp>
#include <Framework/IReceive.hpp>
#include <Framework/TransmitBase.hpp>
#include <Framework/IServiceable.hpp>
#include <Framework/Frame/FrameRequestModel.hpp>

namespace ModbusMaster
{
    class FrameLayer :
            public Framework::IServiceable,
            public Framework::IReceive<Framework::Frame::FrameContent>,
            public Framework::IReceive<Framework::Frame::FrameRequestModel>,
            public Framework::TransmitBase<Framework::Frame::FrameContent>
    {
    public:
        FrameLayer();
        ~FrameLayer();

        void Service(uint64_t ms) override;
        bool Receive(Framework::Frame::FrameRequestModel &frameRequestModel) override;
        bool Receive(Framework::Frame::FrameContent& byte) override;

    private:
        Framework::Frame::FrameHeader _expectedHeader;
        size_t _expectedDataBytesRemaining;
        Framework::IReceive<Framework::Frame::FrameContent>* _callback;

        Framework::Frame::FrameContent _receivedDataBytes;
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
        void PrepareReceive(Framework::Frame::FrameRequestModel &frameRequestModel);
        bool VerifyCrc();
        void Reset();
    };
} // Namespace ModbusMaster.

#endif // FRAMELAYER_HPP
