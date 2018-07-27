#ifndef READINPUTSTRATETY_HPP
#define READINPUTSTRATETY_HPP

#include <RequestModel.hpp>

#include <Framework/Frame/Frame.hpp>
#include <Framework/IReceive.hpp>
#include <Framework/TransmitBase.hpp>

namespace ModbusMaster
{
namespace Strategies
{
    class ReadInputStratety :
            public Framework::IReceive<RequestModel>,
            public Framework::TransmitBase<Framework::Frame>
    {
    public:
        ReadInputStratety();

        bool Receive(RequestModel &data) override;
    };
} // Namespace Strategies.
} // Namespace ModbusMaster.

#endif // READINPUTSTRATETY_HPP
