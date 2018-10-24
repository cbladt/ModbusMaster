#ifndef REQUESTMODEL_HPP
#define REQUESTMODEL_HPP

#include <Framework/FunctionCode.hpp>

#include <cstdint>

namespace ModbusMaster
{
    class RequestModel
    {
    public:
        RequestModel(uint8_t device, Framework::FunctionCode functionCode, uint16_t startAddress, uint16_t count, uint16_t* values = nullptr);

        uint8_t GetDevice() const;

        Framework::FunctionCode GetFunctionCode() const;        

        uint16_t GetStartAddress() const;

        uint16_t GetCount() const;

        uint16_t* GetValues() const;

    private:
        uint8_t _device;
        Framework::FunctionCode _functionCode;
        uint16_t _startAddress;
        uint16_t _count;
        uint16_t* _values;
    };
} // Namespace ModbusMaster.

#endif // REQUESTMODEL_HPP
