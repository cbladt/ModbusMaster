#include "ModbusMaster.hpp"

namespace ModbusMaster
{
    ModbusMaster::ModbusMaster(IDataLink &datalink, IReadRegistersCallback& readRegistersCallback) :
        _datalink(datalink),
        _readInputStrategy(readRegistersCallback),
        _readHoldingStrategy(readRegistersCallback)
    {
        // ModbusMaster -> Framerouter.
        Subscribe(_frameRouter);

        // Framerouter -> Strategy.
        _frameRouter.GetReadInputSubject().Subscribe(_readInputStrategy);
        _frameRouter.GetReadHoldingSubject().Subscribe(_readHoldingStrategy);

        // Strategy -> Framelayer.
        _readInputStrategy.Subscribe(_frameLayer);
        _readHoldingStrategy.Subscribe(_frameLayer);

        // Framelayer -> IDataLink.
        _frameLayer.Subscribe(_datalink);


        // IDataLink -> FrameLayer.
        _datalink.Subscribe(_frameLayer);

        // The strategy in use has told the Framelayer to be called back on.


    }

    void ModbusMaster::Service(uint64_t ms)
    {
        _frameLayer.Service(ms);
    }

    bool ModbusMaster::ReadParameters(uint8_t slave, Framework::FunctionCode type, uint16_t startAddress, uint16_t count)
    {
        if (!SlaveIdIsValid(slave)) return false;

        RequestModel model(slave, type, startAddress, count);
        return Transmit(model);
    }

    bool ModbusMaster::WriteParameters(uint8_t slave, uint16_t startAddress, uint16_t count, uint16_t* values)
    {
        if (!SlaveIdIsValid(slave)) return false;
        if (values == nullptr) return false;

        RequestModel model(slave, Framework::FunctionCode::ReadHolding, startAddress, count, values);
        return Transmit(model);
    }

    bool ModbusMaster::SlaveIdIsValid(uint8_t slaveId) const
    {
        return slaveId <= 247;
    }
} // Namespace ModbusMaster.
