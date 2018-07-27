#ifndef MODBUSPARAMETER_HPP
#define MODBUSPARAMETER_HPP

#include <cstdint>
#include <vector>

namespace ModbusMaster
{
    ///
    /// \brief The ModbusParameter class describes a ModbusParameter.
    /// See Readme.md for difference between register and parameter.
    ///
    class ModbusParameter
    {
    public:
        ModbusParameter(uint16_t address, uint16_t size, const std::vector<uint8_t>& value = std::vector<uint8_t>());

        void Setvalue(const std::vector<uint8_t>& value);

        uint16_t GetAddress() const;

        uint16_t GetSize() const;

        const std::vector<uint8_t>& GetValue() const;
    private:
        uint16_t _address;
        uint16_t _size;
        std::vector<uint8_t> _value;
    };
} // Namespace ModbusMaster.

#endif // MODBUSPARAMETER_HPP
