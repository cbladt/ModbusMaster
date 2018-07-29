#ifndef MODBUSMASTER_HPP
#define MODBUSMASTER_HPP

#include <IDataLink.hpp>
#include <RequestModel.hpp>
#include <FrameRouter.hpp>
#include <FrameLayer.hpp>
#include <Strategies/ReadRegistersStrategy.hpp>
#include <Framework/TransmitBase.hpp>
#include <Framework/Parameter.hpp>

#include <cstdint>
#include <vector>

namespace ModbusMaster
{
    class ModbusMaster :
            public Framework::TransmitBase<RequestModel>
    {
    public:
        ModbusMaster(IDataLink& datalink);

        bool ReadParameters(uint8_t slave, const std::vector<Framework::Parameter>& parameters);

        bool WriteParameters(uint8_t slave, const std::vector<Framework::Parameter>& parameters);

    private:
        bool ReadInputParameters(uint8_t slave, const std::vector<Framework::Parameter>& parameters);
        bool ReadHoldingParameters(uint8_t slave, const std::vector<Framework::Parameter>& parameters);

        IDataLink& _datalink;
        FrameRouter _frameRouter;
        FrameLayer _frameLayer;

        Strategies::ReadRegistersStratety _readInputStrategy;
        Strategies::ReadRegistersStratety _readHoldingStrategy;
    };
} // Namespace ModbusMaster.



#endif // MODBUSMASTER_HPP
