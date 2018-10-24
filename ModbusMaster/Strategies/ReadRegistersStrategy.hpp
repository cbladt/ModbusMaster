#ifndef READINPUTSTRATETY_HPP
#define READINPUTSTRATETY_HPP

#include <IReadRegistersCallback.hpp>

#include <Strategies/StrategyBase.hpp>
#include <Framework/Frame/ReadRegistersFrame.hpp>

namespace ModbusMaster
{
namespace Strategies
{
    class ReadRegistersStratety :
            public StrategyBase
    {
    public:
        ReadRegistersStratety(IReadRegistersCallback& callback);
        ~ReadRegistersStratety() = default;

        void Service(uint64_t ms) final;

        bool Receive(RequestModel &data) final;

        bool Receive(Framework::Frame::FrameContent& data) final;

    private:
        IReadRegistersCallback& _callback;

        bool _isExpecting;
        Framework::Frame::FrameHeader _lastTransmittedFrameHeader;
        uint16_t _lastTransmittedRegisterCount;
        uint16_t _lastTransmittedStartAddress;

        ReadRegistersStratety(const ReadRegistersStratety&) = delete;
        const ReadRegistersStratety& operator=(const ReadRegistersStratety&) = delete;
    };
} // Namespace Strategies.
} // Namespace ModbusMaster.

#endif // READINPUTSTRATETY_HPP
