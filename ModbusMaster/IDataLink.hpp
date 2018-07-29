#ifndef IDATALINK_HPP
#define IDATALINK_HPP

#include <Framework/TransmitBase.hpp>
#include <Framework/IReceive.hpp>

#include <cstdint>
#include <vector>

namespace ModbusMaster
{
    class IDataLink :
            public Framework::IReceive<std::vector<uint8_t>>,
            public Framework::TransmitBase<std::vector<uint8_t>>

    {
    public:
        virtual ~IDataLink() {}

        virtual bool Receive(std::vector<uint8_t>& bytes) = 0;
    };
} // Namespace ModbusMaster.

#endif // IDATALINK_HPP
