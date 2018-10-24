#ifndef TRANSMITBASE_HPP
#define TRANSMITBASE_HPP

#include <Framework/IReceive.hpp>

namespace ModbusMaster
{
namespace Framework
{
    template <typename T>
    class TransmitBase
    {
    public:        
        TransmitBase() :
            _subscriber(nullptr)
        {}

        virtual ~TransmitBase() = default;

        bool Subscribe(IReceive<T>& subscriber) noexcept
        {
            bool status = false;

            if (_subscriber == nullptr)
            {
                _subscriber = &subscriber;
                status = true;
            }

            return status;
        }

        bool Unsubscribe() noexcept
        {
            bool status = false;

            if (_subscriber != nullptr)
            {
                _subscriber = nullptr;
                status = true;
            }

            return status;
        }

        bool Transmit(T& data)
        {
            bool status = false;

            if (_subscriber != nullptr)
            {
                status = _subscriber->Receive(data);
            }

            return status;
        }

    private:
        IReceive<T>* _subscriber;
    };

} // Namespace Framework.
} // Namespace ModbusMaste

#endif // TRANSMITBASE_HPP
