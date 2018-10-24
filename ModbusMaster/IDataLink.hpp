#ifndef IDATALINK_HPP
#define IDATALINK_HPP

#include <Framework/TransmitBase.hpp>
#include <Framework/IReceive.hpp>

#include <Framework/Frame/FrameContent.hpp>

#include <cstdint>

namespace ModbusMaster
{
    class IDataLink :
            public Framework::IReceive<Framework::Frame::FrameContent>,
            public Framework::TransmitBase<Framework::Frame::FrameContent>

    {
    public:
        virtual ~IDataLink() {}

        virtual bool Receive(Framework::Frame::FrameContent& bytes) = 0;
    };
} // Namespace ModbusMaster.

#endif // IDATALINK_HPP
