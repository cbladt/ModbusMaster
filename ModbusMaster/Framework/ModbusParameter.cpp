#include "ModbusParameter.hpp"

namespace ModbusMaster
{
    ModbusParameter::ModbusParameter(uint16_t address, uint16_t size, const std::vector<uint8_t>& value) :
        _address(address),
        _size(size),
        _value(value.cbegin(), value.cend())
    {}

    void ModbusParameter::Setvalue(const std::vector<uint8_t> &value)
    {
        _value = value;
    }

    uint16_t ModbusParameter::GetAddress()
    {
        return _address;
    }

    uint16_t ModbusParameter::GetSize()
    {
        return _size;
    }

    const std::vector<uint8_t>& ModbusParameter::GetValue()
    {
        return _value;
    }
}
