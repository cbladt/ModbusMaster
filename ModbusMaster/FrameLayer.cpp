#include "FrameLayer.hpp"

namespace ModbusMaster
{
    FrameLayer::FrameLayer() :
        _expectedHeader(0,0),
        _receiveState(ReceiveState::Idle)
    {}

    bool FrameLayer::Receive(Framework::Frame::FrameRequestModel &frameRequestModel)
    {
        auto& frame = frameRequestModel.GetFrame();
        auto bytes = frame.GetBytes();

        PrepareReceive(frame.GetFrameHeder(), frameRequestModel.GetExpectedResponseDataBytes());

        return Transmit(bytes);
    }

    bool FrameLayer::Receive(std::vector<uint8_t>& data)
    {
        bool result = true;

        for (auto b : data)
        {
            if (!HandleByte(b))
            {
                result = false;
            }
        }

        return result;
    }

    bool FrameLayer::HandleByte(uint8_t byte)
    {
        switch (_receiveState)
        {
            case ReceiveState::Done: return false;
            case ReceiveState::Idle: return false;

            case ReceiveState::SlaveId:
            {
                if (byte == _expectedHeader.GetSlaveId())
                {
                    _receiveState = ReceiveState::FunctionCode;
                }
                else
                {
                    Reset();
                }

                break;
            }

            case ReceiveState::FunctionCode:
            {
		// tbd : Handle exception!
                if (static_cast<Framework::FunctionCode>(byte) == _expectedHeader.GetFunctionCode())
                {
                    _receiveState = ReceiveState::Data;
                }
                else
                {
                    Reset();
                }

                break;
            }

            case ReceiveState::Data:
            {
                _receivedBytes.push_back(byte);
                _expectedDataBytesRemaining--;

                if (_expectedDataBytesRemaining == 0)
                {
                    _receiveState = ReceiveState::Crc1;
                }

                break;
            }

            case ReceiveState::Crc1:
            {
                _receivedCrc = (_receivedCrc & 0x00ff) | (byte << 8);
                _receiveState = ReceiveState::Crc2;
                break;
            }

            case ReceiveState::Crc2:
            {
                _receivedCrc = (_receivedCrc & 0xff00) | byte;

                if (VerifyCrc())
                {
                    _receiveState = ReceiveState::Done;
                }
                else
                {
                    Reset();
                }
                break;
            }
        }

        return true;
    }

    void FrameLayer::PrepareReceive(Framework::Frame::FrameHeader header, size_t dataBytes)
    {
        _expectedHeader = header;
        _expectedDataBytesRemaining = dataBytes;
        _receiveState = ReceiveState::SlaveId;
    }

    bool FrameLayer::VerifyCrc()
    {
        return true;
    }

    void FrameLayer::Reset()
    {
        _receiveState = ReceiveState::Idle;
    }
} // Namespace ModbusMaster.
