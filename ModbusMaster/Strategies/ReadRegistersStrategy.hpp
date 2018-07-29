#ifndef READINPUTSTRATETY_HPP
#define READINPUTSTRATETY_HPP

#include <Strategies/StrategyBase.hpp>

namespace ModbusMaster
{
namespace Strategies
{
    class ReadRegistersStratety :
            public StrategyBase
    {
    public:
        ReadRegistersStratety();

        bool Receive(RequestModel &data) override;
    };
} // Namespace Strategies.
} // Namespace ModbusMaster.

#endif // READINPUTSTRATETY_HPP
