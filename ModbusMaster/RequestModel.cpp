#include "RequestModel.hpp"

namespace ModbusMaster
{
    RequestModel::RequestModel(uint8_t device, Framework::FunctionCode functionCode, uint16_t startAddress, uint16_t count, uint16_t values[]) :
        _device(device),
        _functionCode(functionCode),
        _startAddress(startAddress),
        _count(count),
        _values(values)
    {}

    uint8_t RequestModel::GetDevice() const
    {
        return _device;
    }

    Framework::FunctionCode RequestModel::GetFunctionCode() const
    {
        return _functionCode;
    }

    uint16_t RequestModel::GetStartAddress() const
    {
        return _startAddress;
    }

    uint16_t RequestModel::GetCount() const
    {
        return _count;
    }

    uint16_t* RequestModel::GetValues() const
    {
        return _values;
    }
} // Namespace ModbusMaster.
