#include "ModbusMaster.hpp"

namespace ModbusMaster
{
    ModbusMaster::ModbusMaster(IDataLink &datalink) :
        _datalink(datalink)
    {
        // ModbusMaster -> Framerouter.
        Subscribe(_frameRouter);

        // Framerouter -> Strategy.
        _frameRouter.GetReadInputSubject().Subscribe(_readInputStrategy);

        // Strategy -> Framelayer.
        _readInputStrategy.Subscribe(_frameLayer);

        // Framelayer -> IDatalink.
        _frameLayer.Subscribe(_datalink);
    }

    bool ModbusMaster::ReadParameters(uint8_t slave, const std::vector<Framework::Parameter> &parameters)
    {
        if (parameters.empty()) return false;

        // Ensure all params are of the same type.
        auto type = parameters.front().GetType();
        for (auto& param : parameters)
        {
            if (param.GetType() != type) return false;
        }

        // Route to the correct method.
        if (type == Framework::ParameterType::Holding)
        {
            return ReadHoldingParameters(slave, parameters);
        }
        else if (type == Framework::ParameterType::Input)
        {
            return ReadInputParameters(slave, parameters);
        }

        return false;
    }

    bool ModbusMaster::WriteParameters(uint8_t slave, const std::vector<Framework::Parameter> &parameters)
    {
        if (parameters.empty()) return false;

        RequestModel model(slave, Framework::FunctionCode::WriteMultiple, parameters);
        return Transmit(model);
    }

    bool ModbusMaster::ReadHoldingParameters(uint8_t slave, const std::vector<Framework::Parameter> &parameters)
    {
        RequestModel model(slave, Framework::FunctionCode::ReadHolding, parameters);
        return Transmit(model);
    }

    bool ModbusMaster::ReadInputParameters(uint8_t slave, const std::vector<Framework::Parameter> &parameters)
    {
        RequestModel model(slave, Framework::FunctionCode::ReadInput, parameters);
        return Transmit(model);
    }
} // Namespace ModbusMaster.
