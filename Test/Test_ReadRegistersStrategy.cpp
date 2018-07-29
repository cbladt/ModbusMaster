#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include <Framework/Frame/ReadRegistersFrame.hpp>
#include <Strategies/ReadRegistersStrategy.hpp>

template <typename T>
class Receiver :
        public ModbusMaster::Framework::IReceive<ModbusMaster::Framework::Frame::FrameRequestModel>
{
public:
    Receiver() :
        _doClean(false)
    {}

    ~Receiver()
    {
        if (_doClean)
        {
            delete _frame;
        }
    }

    bool Receive(ModbusMaster::Framework::Frame::FrameRequestModel& data)
    {
        _frame = new T (static_cast<T&>(data.GetFrame()));
        _doClean = true;
        _expectedDataBytes = data.GetExpectedResponseDataBytes();
        return true;
    }

    T& GetFrame()
    {
        return *_frame;
    }

    size_t GetExpectedDataBytes() const
    {
        return _expectedDataBytes;
    }

private:
    T* _frame;
    size_t _expectedDataBytes;
    bool _doClean;
};

class Callback :
        public ModbusMaster::IReadRegistersCallback
{
public:
    void ReadRegistersCallback(ModbusMaster::Framework::FunctionCode type, uint16_t startAddress, uint16_t count, uint16_t* value)
    {
        (void)type;
        (void)startAddress;
        (void)count;
        (void)value;
    }
};

TEST(Strategies_ReadRegistersStrategy, ReceiveRequestModel_Holding)
{
    static const uint16_t STARTADDRESS = 1234;
    static const uint16_t COUNT = 127;
    static const auto FUNCTION = ModbusMaster::Framework::FunctionCode::ReadHolding;
    static const uint8_t DEVICE = 10;

    // Setup transmit/receive (Strategy -> Receiver)
    Callback callback;
    ModbusMaster::Strategies::ReadRegistersStratety strat(callback);
    Receiver<ModbusMaster::Framework::Frame::ReadRegistersFrame> receiver;
    strat.Subscribe(receiver);

    // Create valid request model to send.
    ModbusMaster::RequestModel model(DEVICE, FUNCTION, STARTADDRESS, COUNT);

    // Assert outcome.
    ASSERT_TRUE(strat.Receive(model));
    ASSERT_EQ(receiver.GetFrame().GetFrameHeder().GetSlaveId(), DEVICE);
    ASSERT_EQ(receiver.GetFrame().GetFrameHeder().GetFunctionCode(), FUNCTION);
    ASSERT_EQ(receiver.GetFrame().GetCount(), COUNT);
    ASSERT_EQ(receiver.GetFrame().GetStartAddress(), STARTADDRESS);
    ASSERT_EQ(receiver.GetExpectedDataBytes(), static_cast<size_t>((model.GetCount() * 2) + 1));
}

TEST(Strategies_ReadRegistersStrategy, ReceiveRequestModel_Holding_TooManyParams)
{
    static const uint16_t STARTADDRESS = 1234;
    static const uint16_t COUNT = 128;
    static const auto FUNCTION = ModbusMaster::Framework::FunctionCode::ReadHolding;
    static const uint8_t DEVICE = 10;

    // Setup transmit/receive (Strategy -> Receiver)
    Callback callback;
    ModbusMaster::Strategies::ReadRegistersStratety strat(callback);
    Receiver<ModbusMaster::Framework::Frame::ReadRegistersFrame> receiver;
    strat.Subscribe(receiver);

    // Create valid request model to send.
    ModbusMaster::RequestModel model(DEVICE, FUNCTION, STARTADDRESS, COUNT);

    // Assert outcome.
    ASSERT_FALSE(strat.Receive(model));
}

TEST(Strategies_ReadRegistersStrategy, ReceiveRequestModel_Input)
{
    static const uint16_t STARTADDRESS = 1234;
    static const uint16_t COUNT = 127;
    static const auto FUNCTION = ModbusMaster::Framework::FunctionCode::ReadInput;
    static const uint8_t DEVICE = 10;

    // Setup transmit/receive (Strategy -> Receiver)
    Callback callback;
    ModbusMaster::Strategies::ReadRegistersStratety strat(callback);
    Receiver<ModbusMaster::Framework::Frame::ReadRegistersFrame> receiver;
    strat.Subscribe(receiver);

    // Create valid request model to send.
    ModbusMaster::RequestModel model(DEVICE, FUNCTION, STARTADDRESS, COUNT);

    // Assert outcome.
    ASSERT_TRUE(strat.Receive(model));
    ASSERT_EQ(receiver.GetFrame().GetFrameHeder().GetSlaveId(), DEVICE);
    ASSERT_EQ(receiver.GetFrame().GetFrameHeder().GetFunctionCode(), FUNCTION);
    ASSERT_EQ(receiver.GetFrame().GetCount(), COUNT);
    ASSERT_EQ(receiver.GetFrame().GetStartAddress(), STARTADDRESS);
    ASSERT_EQ(receiver.GetExpectedDataBytes(), static_cast<size_t>((model.GetCount() * 2) + 1));
}

TEST(Strategies_ReadRegistersStrategy, ReceiveRequestModel_Input_TooManyParams)
{
    static const uint16_t STARTADDRESS = 1234;
    static const uint16_t COUNT = 128;
    static const auto FUNCTION = ModbusMaster::Framework::FunctionCode::ReadInput;
    static const uint8_t DEVICE = 10;

    // Setup transmit/receive (Strategy -> Receiver)
    Callback callback;
    ModbusMaster::Strategies::ReadRegistersStratety strat(callback);
    Receiver<ModbusMaster::Framework::Frame::ReadRegistersFrame> receiver;
    strat.Subscribe(receiver);

    // Create valid request model to send.
    ModbusMaster::RequestModel model(DEVICE, FUNCTION, STARTADDRESS, COUNT);

    // Assert outcome.
    ASSERT_FALSE(strat.Receive(model));
}
