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

        const std::vector<uint8_t>& GetBytes() override;

        FrameHeader GetFrameHeder() const override;

        uint16_t GetStartAddress() const;

        uint16_t GetCount() const;

    private:
        FrameHeader _header;
        uint16_t _startAddress;
        uint16_t _count;

        std::vector<uint8_t> _bytes;
    };
} // Namespace Frame.
} // Namespace Framework.
} // Namespace ModbusMaster.

#endif // READREGISTERSFRAME_HPP
