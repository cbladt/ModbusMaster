#ifndef FUNCTIONCODE_HPP
#define FUNCTIONCODE_HPP

namespace ModbusMaster
{
namespace Framework
{
    enum class FunctionCode
    {
        ReadHolding = 3,
        ReadInput = 4,
        WriteMultiple = 10
    };
} // Namespace Framework.
} // Namespace ModbusMaster.

#endif // FUNCTIONCODE_HPP
