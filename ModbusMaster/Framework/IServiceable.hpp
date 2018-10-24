#ifndef ISERVICEABLE_HPP
#define ISERVICEABLE_HPP

#include <cstdint>

namespace ModbusMaster
{
namespace Framework
{
    class IServiceable
    {
    public:
        virtual ~IServiceable() = default;
        virtual void Service(uint64_t ms) = 0;
    };
}
}

#endif // ISERVICEABLE_HPP
