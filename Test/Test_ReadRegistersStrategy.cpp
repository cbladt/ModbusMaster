#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

static const uint16_t ADDRESSa = 1234;
static const uint16_t ADDRESSb = 1235;
static const uint16_t ADDRESSc = 1236;
static const uint16_t COUNT = 3;

#include <Framework/Frame/ReadRegistersFrame.hpp>
#include <Strategies/ReadRegistersStrategy.hpp>

template <typename T>
class Receiver :
        public ModbusMaster::Framework::IReceive<ModbusMaster::Framework::Frame::IFrame>
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

    bool Receive(ModbusMaster::Framework::Frame::IFrame& data)
    {
        _frame = new T (static_cast<T&>(data));
        _doClean = true;
        return true;
    }

    T& GetFrame()
    {
        return *_frame;
    }

private:
    T* _frame;
    bool _doClean;
};

TEST(Strategies_ReadRegistersStrategy, ReceiveRequestModel_Holding)
{
    static const auto FUNCTION = ModbusMaster::Framework::FunctionCode::ReadHolding;
    static const auto TYPE = ModbusMaster::Framework::ParameterType::Holding;
    static const uint8_t DEVICE = 10;

    // Setup transmit/receive (Strategy -> Receiver)
    ModbusMaster::Strategies::ReadRegistersStratety strat;
    Receiver<ModbusMaster::Framework::Frame::ReadRegistersFrame> receiver;
    strat.Subscribe(receiver);

    // Create valid request model to send.
    std::vector<ModbusMaster::Framework::Parameter> params =
    {
        ModbusMaster::Framework::Parameter(ADDRESSa, TYPE, 1),
        ModbusMaster::Framework::Parameter(ADDRESSb, TYPE, 1),
        ModbusMaster::Framework::Parameter(ADDRESSc, TYPE, 1)
    };
    ModbusMaster::RequestModel model(DEVICE, FUNCTION, params);

    // Assert outcome.
    ASSERT_TRUE(strat.Receive(model));
    ASSERT_EQ(receiver.GetFrame().GetFrameHeder().GetSlaveId(), DEVICE);
    ASSERT_EQ(receiver.GetFrame().GetFrameHeder().GetFunctionCode(), FUNCTION);
}

TEST(Strategies_ReadRegistersStrategy, ReceiveRequestModel_Input)
{
    static const auto FUNCTION = ModbusMaster::Framework::FunctionCode::ReadInput;
    static const auto TYPE = ModbusMaster::Framework::ParameterType::Input;
    static const uint8_t DEVICE = 10;

    // Setup transmit/receive (Strategy -> Receiver)
    ModbusMaster::Strategies::ReadRegistersStratety strat;
    Receiver<ModbusMaster::Framework::Frame::ReadRegistersFrame> receiver;
    strat.Subscribe(receiver);

    // Create valid request model to send.
    std::vector<ModbusMaster::Framework::Parameter> params =
    {
        ModbusMaster::Framework::Parameter(ADDRESSa, TYPE, 1),
        ModbusMaster::Framework::Parameter(ADDRESSb, TYPE, 1),
        ModbusMaster::Framework::Parameter(ADDRESSc, TYPE, 1)
    };
    ModbusMaster::RequestModel model(DEVICE, FUNCTION, params);

    // Assert outcome.
    ASSERT_TRUE(strat.Receive(model));
    ASSERT_EQ(receiver.GetFrame().GetFrameHeder().GetSlaveId(), DEVICE);
    ASSERT_EQ(receiver.GetFrame().GetFrameHeder().GetFunctionCode(), FUNCTION);
}

TEST(Strategies_ReadRegistersStrategy, ReceiveRequestModel_TooManyParamsA)
{
    // 127 should be OK.
    static const size_t TESTAMOUNT = 127;

    static const auto FUNCTION = ModbusMaster::Framework::FunctionCode::ReadInput;
    static const auto TYPE = ModbusMaster::Framework::ParameterType::Input;
    static const uint8_t DEVICE = 10;

    // Setup transmit/receive (Strategy -> Receiver)
    ModbusMaster::Strategies::ReadRegistersStratety strat;
    Receiver<ModbusMaster::Framework::Frame::ReadRegistersFrame> receiver;
    strat.Subscribe(receiver);

    // Create valid request model to send.
    std::vector<ModbusMaster::Framework::Parameter> params;
    for (size_t n = 0; n < TESTAMOUNT; n++)
    {
        params.push_back(ModbusMaster::Framework::Parameter(ADDRESSa, TYPE, 1));
    };

    ASSERT_EQ(params.size(), TESTAMOUNT);
    ModbusMaster::RequestModel model(DEVICE, FUNCTION, params);

    // Assert outcome.
    ASSERT_TRUE(strat.Receive(model));
    ASSERT_EQ(receiver.GetFrame().GetFrameHeder().GetSlaveId(), DEVICE);
    ASSERT_EQ(receiver.GetFrame().GetFrameHeder().GetFunctionCode(), FUNCTION);
}

TEST(Strategies_ReadRegistersStrategy, ReceiveRequestModel_TooManyParamsB)
{
    // 128 should be too much.
    static const size_t TESTAMOUNT = 128;

    static const auto FUNCTION = ModbusMaster::Framework::FunctionCode::ReadInput;
    static const auto TYPE = ModbusMaster::Framework::ParameterType::Input;
    static const uint8_t DEVICE = 10;

    // Setup transmit/receive (Strategy -> Receiver)
    ModbusMaster::Strategies::ReadRegistersStratety strat;
    Receiver<ModbusMaster::Framework::Frame::ReadRegistersFrame> receiver;
    strat.Subscribe(receiver);

    // Create valid request model to send.
    std::vector<ModbusMaster::Framework::Parameter> params;
    for (size_t n = 0; n < TESTAMOUNT; n++)
    {
        params.push_back(ModbusMaster::Framework::Parameter(ADDRESSa, TYPE, 1));
    };

    ASSERT_EQ(params.size(), TESTAMOUNT);
    ModbusMaster::RequestModel model(DEVICE, FUNCTION, params);

    // Assert outcome.
    ASSERT_FALSE(strat.Receive(model));
}
