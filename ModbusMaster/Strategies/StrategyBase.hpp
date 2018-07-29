#ifndef STRATEGYBASE_HPP
#define STRATEGYBASE_HPP

#include <RequestModel.hpp>
#include <Framework/Frame/FrameRequestModel.hpp>
#include <Framework/IReceive.hpp>
#include <Framework/TransmitBase.hpp>

namespace ModbusMaster
{
namespace Strategies
{
    class StrategyBase :
            public Framework::IReceive<RequestModel>,
            public Framework::TransmitBase<Framework::Frame::FrameRequestModel>
    {};
} // Namespace Strategies.
} // Namespace ModbusMaster.

#endif // STRATEGYBASE_HPP
