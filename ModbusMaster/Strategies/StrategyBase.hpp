#ifndef STRATEGYBASE_HPP
#define STRATEGYBASE_HPP

#include <RequestModel.hpp>

#include <Framework/IServiceable.hpp>
#include <Framework/IReceive.hpp>
#include <Framework/TransmitBase.hpp>

#include <Framework/Frame/FrameRequestModel.hpp>

namespace ModbusMaster
{
namespace Strategies
{
    class StrategyBase :
            public Framework::IServiceable,
            public Framework::IReceive<RequestModel>,
            public Framework::IReceive<Framework::Frame::FrameContent>,
            public Framework::TransmitBase<Framework::Frame::FrameRequestModel>
    {};
} // Namespace Strategies.
} // Namespace ModbusMaster.

#endif // STRATEGYBASE_HPP
