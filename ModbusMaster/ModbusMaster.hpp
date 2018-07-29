#ifndef MODBUSMASTER_HPP
#define MODBUSMASTER_HPP

#include <IDataLink.hpp>
#include <IReadRegistersCallback.hpp>

#include <RequestModel.hpp>
#include <FrameRouter.hpp>
#include <FrameLayer.hpp>

#include <Strategies/ReadRegistersStrategy.hpp>

#include <Framework/IServiceable.hpp>
#include <Framework/FunctionCode.hpp>
#include <Framework/TransmitBase.hpp>

#include <cstdint>
#include <vector>

namespace ModbusMaster
{
    class ModbusMaster :
            public FrameLayer::IServiceable,
            protected Framework::TransmitBase<RequestModel>
    {
    public:
        ModbusMaster(IDataLink& datalink, IReadRegistersCallback& readRegistersCallback);

        void Service(uint64_t ms) override;

        bool ReadParameters(uint8_t slave, Framework::FunctionCode type, uint16_t startAddress, uint16_t count);

        bool WriteParameters(uint8_t slave, uint16_t startAddress, uint16_t count, uint16_t* values);

    private:
        bool SlaveIdIsValid(uint8_t slaveId) const;

        IDataLink& _datalink;
        FrameRouter _frameRouter;
        FrameLayer _frameLayer;

        Strategies::ReadRegistersStratety _readInputStrategy;
        Strategies::ReadRegistersStratety _readHoldingStrategy;
    };
} // Namespace ModbusMaster.



#endif // MODBUSMASTER_HPP
