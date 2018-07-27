#ifndef IDATALINK_HPP
#define IDATALINK_HPP

#include <Framework/IReceive.hpp>

#include <cstdint>
#include <vector>

namespace ModbusMaster
{
    class IDataLink :
            public Framework::IReceive<std::vector<uint8_t>>

    {
    public:
        virtual ~IDataLink() {}

        bool Receive(std::vector<uint8_t>& bytes) override;
    };
} // Namespace ModbusMaster.

#endif // IDATALINK_HPP
