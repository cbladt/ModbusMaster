#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include <FrameRouter.hpp>

class Receiver :
        public ModbusMaster::Framework::IReceive<ModbusMaster::RequestModel>
{
public:
    Receiver() :
        _hasReceived(false)
    {}

    bool Receive(ModbusMaster::RequestModel &model) override
    {
        _hasReceived = true;
        _model = &model;
        return true;
    }

    bool HasReceived() const
    {
        return _hasReceived;
    }

    ModbusMaster::RequestModel& GetModel()
    {
        return *_model;
    }

private:
    bool _hasReceived;
    ModbusMaster::RequestModel* _model;
};

TEST(FrameRouter, RequestModel_ReadInput)
{
    static const uint8_t SLAVEID = 10;
    static const size_t COUNT = 3;
    static const uint8_t MODBUSADDR_A = 1;
    static const uint8_t MODBUSADDR_B = 2;
    static const uint8_t MODBUSADDR_C = 3;

    // Subscribe Router -> Receiver.
    Receiver inputReceiver;
    Receiver holdingReceiver;
    Receiver writeMultipleReceiver;
    ModbusMaster::FrameRouter router;
    router.GetReadInputSubject().Subscribe(inputReceiver);
    router.GetReadHoldingSubject().Subscribe(holdingReceiver);
    router.GetWriteMutipleSubject().Subscribe(writeMultipleReceiver);

    // Verify everything is reset.
    ASSERT_FALSE(inputReceiver.HasReceived());
    ASSERT_FALSE(holdingReceiver.HasReceived());
    ASSERT_FALSE(writeMultipleReceiver.HasReceived());

    // Create model.
    std::vector<ModbusMaster::Framework::Parameter> params =
    {
        ModbusMaster::Framework::Parameter(MODBUSADDR_A, ModbusMaster::Framework::ParameterType::Input, 1),
        ModbusMaster::Framework::Parameter(MODBUSADDR_B, ModbusMaster::Framework::ParameterType::Input, 1),
        ModbusMaster::Framework::Parameter(MODBUSADDR_C, ModbusMaster::Framework::ParameterType::Input, 1)
    };
    ModbusMaster::RequestModel model(SLAVEID, ModbusMaster::Framework::FunctionCode::ReadInput, params);

    // Model -> Router.
    router.Receive(model);

    // Assert that Router -> Receiver.
    ASSERT_TRUE(inputReceiver.HasReceived());
    ASSERT_EQ(inputReceiver.GetModel().GetDevice(), SLAVEID);
    ASSERT_EQ(inputReceiver.GetModel().GetParameters().size(), COUNT);
    ASSERT_EQ(inputReceiver.GetModel().GetParameters()[0].GetAddress(), MODBUSADDR_A);
    ASSERT_EQ(inputReceiver.GetModel().GetParameters()[1].GetAddress(), MODBUSADDR_B);
    ASSERT_EQ(inputReceiver.GetModel().GetParameters()[2].GetAddress(), MODBUSADDR_C);

    // Assert that nothing got to the other subjects.
    ASSERT_FALSE(holdingReceiver.HasReceived());
    ASSERT_FALSE(writeMultipleReceiver.HasReceived());
}

TEST(FrameRouter, RequestModel_ReadHolding)
{
    static const uint8_t SLAVEID = 10;
    static const size_t COUNT = 3;
    static const uint8_t MODBUSADDR_A = 1;
    static const uint8_t MODBUSADDR_B = 2;
    static const uint8_t MODBUSADDR_C = 3;

    // Subscribe Router -> Receiver.
    Receiver inputReceiver;
    Receiver holdingReceiver;
    Receiver writeMultipleReceiver;
    ModbusMaster::FrameRouter router;
    router.GetReadInputSubject().Subscribe(inputReceiver);
    router.GetReadHoldingSubject().Subscribe(holdingReceiver);
    router.GetWriteMutipleSubject().Subscribe(writeMultipleReceiver);

    // Verify everything is reset.
    ASSERT_FALSE(inputReceiver.HasReceived());
    ASSERT_FALSE(holdingReceiver.HasReceived());
    ASSERT_FALSE(writeMultipleReceiver.HasReceived());

    // Create model.
    std::vector<ModbusMaster::Framework::Parameter> params =
    {
        ModbusMaster::Framework::Parameter(MODBUSADDR_A, ModbusMaster::Framework::ParameterType::Holding, 1),
        ModbusMaster::Framework::Parameter(MODBUSADDR_B, ModbusMaster::Framework::ParameterType::Holding, 1),
        ModbusMaster::Framework::Parameter(MODBUSADDR_C, ModbusMaster::Framework::ParameterType::Holding, 1)
    };
    ModbusMaster::RequestModel model(SLAVEID, ModbusMaster::Framework::FunctionCode::ReadHolding, params);

    // Model -> Router.
    router.Receive(model);

    // Assert that Router -> Receiver.
    ASSERT_TRUE(holdingReceiver.HasReceived());
    ASSERT_EQ(holdingReceiver.GetModel().GetDevice(), SLAVEID);
    ASSERT_EQ(holdingReceiver.GetModel().GetParameters().size(), COUNT);
    ASSERT_EQ(holdingReceiver.GetModel().GetParameters()[0].GetAddress(), MODBUSADDR_A);
    ASSERT_EQ(holdingReceiver.GetModel().GetParameters()[1].GetAddress(), MODBUSADDR_B);
    ASSERT_EQ(holdingReceiver.GetModel().GetParameters()[2].GetAddress(), MODBUSADDR_C);

    // Assert that nothing got to the other subjects.
    ASSERT_FALSE(inputReceiver.HasReceived());
    ASSERT_FALSE(writeMultipleReceiver.HasReceived());
}

TEST(FrameRouter, RequestModel_WriteMultiple)
{
    static const uint8_t SLAVEID = 10;
    static const size_t COUNT = 3;
    static const uint8_t MODBUSADDR_A = 1;
    static const uint8_t MODBUSADDR_B = 2;
    static const uint8_t MODBUSADDR_C = 3;

    // Subscribe Router -> Receiver.
    Receiver inputReceiver;
    Receiver holdingReceiver;
    Receiver writeMultipleReceiver;
    ModbusMaster::FrameRouter router;
    router.GetReadInputSubject().Subscribe(inputReceiver);
    router.GetReadHoldingSubject().Subscribe(holdingReceiver);
    router.GetWriteMutipleSubject().Subscribe(writeMultipleReceiver);

    // Verify everything is reset.
    ASSERT_FALSE(inputReceiver.HasReceived());
    ASSERT_FALSE(holdingReceiver.HasReceived());
    ASSERT_FALSE(writeMultipleReceiver.HasReceived());

    // Create model.
    std::vector<ModbusMaster::Framework::Parameter> params =
    {
        ModbusMaster::Framework::Parameter(MODBUSADDR_A, ModbusMaster::Framework::ParameterType::Holding, 1),
        ModbusMaster::Framework::Parameter(MODBUSADDR_B, ModbusMaster::Framework::ParameterType::Holding, 1),
        ModbusMaster::Framework::Parameter(MODBUSADDR_C, ModbusMaster::Framework::ParameterType::Holding, 1)
    };
    ModbusMaster::RequestModel model(SLAVEID, ModbusMaster::Framework::FunctionCode::WriteMultiple, params);

    // Model -> Router.
    router.Receive(model);

    // Assert that Router -> Receiver.
    ASSERT_TRUE(writeMultipleReceiver.HasReceived());
    ASSERT_EQ(writeMultipleReceiver.GetModel().GetDevice(), SLAVEID);
    ASSERT_EQ(writeMultipleReceiver.GetModel().GetParameters().size(), COUNT);
    ASSERT_EQ(writeMultipleReceiver.GetModel().GetParameters()[0].GetAddress(), MODBUSADDR_A);
    ASSERT_EQ(writeMultipleReceiver.GetModel().GetParameters()[1].GetAddress(), MODBUSADDR_B);
    ASSERT_EQ(writeMultipleReceiver.GetModel().GetParameters()[2].GetAddress(), MODBUSADDR_C);

    // Assert that nothing got to the other subjects.
    ASSERT_FALSE(inputReceiver.HasReceived());
    ASSERT_FALSE(holdingReceiver.HasReceived());
}
