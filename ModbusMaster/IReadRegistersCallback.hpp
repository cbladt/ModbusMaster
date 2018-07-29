#ifndef IREADREGISTERSCALLBACK_HPP
#define IREADREGISTERSCALLBACK_HPP

#include <Framework/FunctionCode.hpp>
#include <cstdint>

namespace ModbusMaster
{
    class IReadRegistersCallback
    {
    public:
        virtual ~IReadRegistersCallback() {}

        virtual void ReadRegistersCallback(Framework::FunctionCode type, uint16_t startAddress, uint16_t count, uint16_t* value) = 0;
    };
} // Namespace ModbusMaster.

#endif // READREGISTERSCALLBACK_HPP
