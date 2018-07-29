#ifndef FRAMEROUTER_HPP
#define FRAMEROUTER_HPP

#include <RequestModel.hpp>

#include <Strategies/ReadRegistersStrategy.hpp>

#include <Framework/IReceive.hpp>
#include <Framework/TransmitBase.hpp>

#include <cstdint>

namespace ModbusMaster
{
    class FrameRouter :            
            public Framework::IReceive<RequestModel>
    {
    public:
        FrameRouter();

        bool Receive(RequestModel& data) override;

        Framework::TransmitBase<RequestModel>& GetReadInputSubject();
        Framework::TransmitBase<RequestModel>& GetReadHoldingSubject();
        Framework::TransmitBase<RequestModel>& GetWriteMutipleSubject();

    private:        
        Framework::TransmitBase<RequestModel> _readInputSubject;
        Framework::TransmitBase<RequestModel> _readHoldingSubject;
        Framework::TransmitBase<RequestModel> _writeMultipleSubject;
    };
} // Namespace ModbusMaster.

#endif // FRAMEROUTER_HPP
