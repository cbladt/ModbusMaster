#ifndef IRECEIVE_HPP
#define IRECEIVE_HPP

namespace ModbusMaster
{
namespace Framework
{
    template <typename T>
    class IReceive
    {
    public:
        virtual ~IReceive() = default;
        virtual bool Receive(T&) = 0;
    };

} // Namespace IReceive.
} // Namespace ModbusMaster.

#endif // IRECEIVE_HPP
