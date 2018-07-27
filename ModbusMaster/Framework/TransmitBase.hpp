#ifndef TRANSMITBASE_HPP
#define TRANSMITBASE_HPP

#include <Framework/IReceive.hpp>

#include <vector>

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

        bool Transmit(T& data)
        {
            if (_subscriber == nullptr) return false;

            return _subscriber->Receive(data);
        }

        bool Subscribe(IReceive<T>& subscriber)
        {
            if (_subscriber == nullptr)
            {
                _subscriber = &subscriber;
                return true;
            }

            return false;
        }

        bool Unsubscribe()
        {
            if (_subscriber == nullptr)
            {
                return false;
            }
            else
            {
                _subscriber = nullptr;
                return true;
            }
        }

    private:
        IReceive<T>* _subscriber;
    };

} // Namespace Framework.
} // Namespace ModbusMaste

#endif // TRANSMITBASE_HPP
