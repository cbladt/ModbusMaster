#include "Parameter.hpp"

namespace ModbusMaster
{
namespace Framework
{
    Parameter::Parameter(uint16_t address, ParameterType type, uint16_t size, const std::vector<uint8_t>& value) :
        _address(address),
        _type(type),
        _size(size),
        _value(value.cbegin(), value.cend())
    {}

    void Parameter::Setvalue(const std::vector<uint8_t> &value)
    {
        _value = value;
    }

    ParameterType Parameter::GetType() const
    {
        return _type;
    }

    uint16_t Parameter::GetAddress() const
    {
        return _address;
    }

    uint16_t Parameter::GetSize() const
    {
        return _size;
    }

    const std::vector<uint8_t>& Parameter::GetValue() const
    {
        return _value;
    }
} // Namespace Framework.
} // Namespace ModbusMaster.
