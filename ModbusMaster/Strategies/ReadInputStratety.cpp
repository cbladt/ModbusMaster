#include "ReadInputStratety.hpp"

namespace ModbusMaster
{
namespace Strategies
{
    ReadInputStratety::ReadInputStratety()
    {}

    bool ReadInputStratety::Receive(RequestModel &data)
    {
        (void)data;
        return true;
    }
} // Namespace Strategies.
} // Namespace ModbusMaster.
