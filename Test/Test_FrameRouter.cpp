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
    static const uint16_t COUNT = 3;
    static const uint16_t STARTADDRESS = 1337;

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
    ModbusMaster::RequestModel model(SLAVEID, ModbusMaster::Framework::FunctionCode::ReadInput, STARTADDRESS, COUNT);

    // Model -> Router.
    ASSERT_TRUE(router.Receive(model));

    // Assert that Router -> Receiver.
    ASSERT_TRUE(inputReceiver.HasReceived());
    ASSERT_EQ(inputReceiver.GetModel().GetDevice(), SLAVEID);
    ASSERT_EQ(inputReceiver.GetModel().GetStartAddress(), STARTADDRESS);
    ASSERT_EQ(inputReceiver.GetModel().GetCount(), COUNT);
    ASSERT_EQ(inputReceiver.GetModel().GetValues(), nullptr);

    // Assert that nothing got to the other subjects.
    ASSERT_FALSE(holdingReceiver.HasReceived());
    ASSERT_FALSE(writeMultipleReceiver.HasReceived());
}

TEST(FrameRouter, RequestModel_ReadHolding)
{
    static const uint8_t SLAVEID = 10;
    static const uint16_t COUNT = 3;
    static const uint16_t STARTADDRESS = 1337;

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
    ModbusMaster::RequestModel model(SLAVEID, ModbusMaster::Framework::FunctionCode::ReadHolding, STARTADDRESS, COUNT);

    // Model -> Router.
    ASSERT_TRUE(router.Receive(model));

    // Assert that Router -> Receiver.
    ASSERT_TRUE(holdingReceiver.HasReceived());
    ASSERT_EQ(holdingReceiver.GetModel().GetDevice(), SLAVEID);
    ASSERT_EQ(holdingReceiver.GetModel().GetStartAddress(), STARTADDRESS);
    ASSERT_EQ(holdingReceiver.GetModel().GetCount(), COUNT);
    ASSERT_EQ(inputReceiver.GetModel().GetValues(), nullptr);

    // Assert that nothing got to the other subjects.
    ASSERT_FALSE(inputReceiver.HasReceived());
    ASSERT_FALSE(writeMultipleReceiver.HasReceived());
}

TEST(FrameRouter, RequestModel_WriteMultiple)
{
    static const uint8_t SLAVEID = 10;
    static const uint16_t COUNT = 3;
    static const uint16_t STARTADDRESS = 1337;
    uint16_t values[] = { 1234, 2345, 3456 };

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
    ModbusMaster::RequestModel model(SLAVEID, ModbusMaster::Framework::FunctionCode::WriteMultiple, STARTADDRESS, COUNT, values);

    // Model -> Router.
    router.Receive(model);

    // Assert that Router -> Receiver.
    ASSERT_TRUE(writeMultipleReceiver.HasReceived());
    ASSERT_EQ(writeMultipleReceiver.GetModel().GetDevice(), SLAVEID);
    ASSERT_EQ(writeMultipleReceiver.GetModel().GetStartAddress(), STARTADDRESS);
    ASSERT_EQ(writeMultipleReceiver.GetModel().GetCount(), COUNT);
    ASSERT_EQ(writeMultipleReceiver.GetModel().GetValues()[0], values[0]);
    ASSERT_EQ(writeMultipleReceiver.GetModel().GetValues()[1], values[1]);
    ASSERT_EQ(writeMultipleReceiver.GetModel().GetValues()[2], values[2]);

    // Assert that nothing got to the other subjects.
    ASSERT_FALSE(inputReceiver.HasReceived());
    ASSERT_FALSE(holdingReceiver.HasReceived());
}

