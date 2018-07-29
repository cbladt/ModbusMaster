#ifndef PARAMETER_HPP
#define PARAMETER_HPP

#include <Framework/ParameterType.hpp>

#include <cstdint>
#include <cstddef>
#include <vector>

namespace ModbusMaster
{
namespace Framework
{
    ///
    /// \brief The ModbusParameter class describes a ModbusParameter.
    /// See Readme.md for difference between register and parameter.
    ///
    class Parameter
    {
    public:
        Parameter(uint16_t address, ParameterType type, size_t size, const std::vector<uint8_t>& value = std::vector<uint8_t>());

        void Setvalue(const std::vector<uint8_t>& value);

        ParameterType GetType() const;

        uint16_t GetAddress() const;

        size_t GetSize() const;

        const std::vector<uint8_t>& GetValue() const;
    private:
        uint16_t _address;
        ParameterType _type;
        size_t _size;
        std::vector<uint8_t> _value;
    };
} // Namespace Framework.
} // Namespace ModbusMaster.

#endif // MODBUSPARAMETER_HPP
