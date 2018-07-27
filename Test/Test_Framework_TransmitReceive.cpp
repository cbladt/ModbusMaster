#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include <Framework/IReceive.hpp>
#include <Framework/TransmitBase.hpp>

#include <iostream>

template <typename T>
class ReceiveStub :
        public ModbusMaster::Framework::IReceive<T>
{
public:
    ReceiveStub() :
        _returnValue(true),
        _hasReceived(false)
    {}

    bool Receive(T& data)
    {
        _data = &data;
        _hasReceived = true;
        return _returnValue;
    }

    bool GetHasReceived() const
    {
        return _hasReceived;
    }

    void SetReturnValue(bool val)
    {
        _returnValue = val;
    }

    T& GetData()
    {
        return *_data;
    }

private:
    bool _returnValue;
    bool _hasReceived;
    T* _data;
};

class ObjectStub
{
public:
    ObjectStub(uint8_t value) :
        _value(value)
    {}

    // Throw up if we copy object.
    ObjectStub(const ObjectStub&)
    {
        std::cout << "ObjectStub got copied!" << std::endl;
        throw;
    }
    ObjectStub(ObjectStub&)
    {
        std::cout << "ObjectStub got copied!" << std::endl;
        throw;
    }

    bool operator==(const ObjectStub& other) const
    {
        return other._value == _value;
    }

private:
    uint8_t _value;
};

TEST(Framework_TransmitReceive, Subscribe_Unsubscribe)
{
    uint8_t VALUE = 123;
    ReceiveStub<decltype(VALUE)> receiver;
    ModbusMaster::Framework::TransmitBase<decltype(VALUE)> transmitter;

    // We should not be able to do these, as we have not subscribed or transmitted yet..
    ASSERT_FALSE(transmitter.Transmit(VALUE));
    ASSERT_FALSE(transmitter.Unsubscribe());
    ASSERT_FALSE(receiver.GetHasReceived());

    // Subscribe..
    ASSERT_TRUE(transmitter.Subscribe(receiver));

    // Now we should be able to transmit.
    ASSERT_TRUE(transmitter.Transmit(VALUE));
    ASSERT_TRUE(receiver.GetHasReceived());

    // Unsubscribe..
    ASSERT_TRUE(transmitter.Unsubscribe());

    // Now we should be able to transmit.
    ASSERT_FALSE(transmitter.Transmit(VALUE));
}

TEST(Framework_TransmitReceive, Transmit)
{
    ObjectStub VALUE (123);
    ReceiveStub<decltype(VALUE)> receiver;
    ModbusMaster::Framework::TransmitBase<decltype(VALUE)> transmitter;

    ASSERT_TRUE(transmitter.Subscribe(receiver));

    // Now we should be able to transmit.
    ASSERT_TRUE(transmitter.Transmit(VALUE));
    ASSERT_TRUE(receiver.GetHasReceived());
    ASSERT_EQ(receiver.GetData(), VALUE);
}
