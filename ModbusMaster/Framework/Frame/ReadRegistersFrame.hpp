#ifndef READREGISTERSFRAME_HPP
#define READREGISTERSFRAME_HPP

#include <Framework/Frame/IFrame.hpp>

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    class ReadRegistersFrame :
            public IFrame
    {
    public:
        ReadRegistersFrame(FrameHeader header, uint16_t startAddress, uint16_t count);
        ~ReadRegistersFrame() = default;

        FrameContent& GetBytes() final;

        FrameHeader GetFrameHeder() const final;

        uint16_t GetStartAddress() const;

        uint16_t GetCount() const;

    private:
        FrameHeader _header;
        uint16_t _startAddress;
        uint16_t _count;

        FrameContent _bytes;

        ReadRegistersFrame(const ReadRegistersFrame&) = delete;
        const ReadRegistersFrame& operator=(const ReadRegistersFrame&) = delete;
    };
} // Namespace Frame.
} // Namespace Framework.
} // Namespace ModbusMaster.

#endif // READREGISTERSFRAME_HPP
