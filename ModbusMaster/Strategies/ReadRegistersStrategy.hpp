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

        void Service(uint64_t ms) override;

        bool Receive(RequestModel &data) override;

        bool Receive(std::vector<uint8_t>& data) override;

    private:
        IReadRegistersCallback& _callback;

        bool _isExpecting;
        Framework::Frame::ReadRegistersFrame _lastTransmittedFrame;
    };
} // Namespace Strategies.
} // Namespace ModbusMaster.

#endif // READINPUTSTRATETY_HPP
