#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include <ModbusMaster.hpp>
#include <IDataLink.hpp>

class Datalink :
        public ModbusMaster::IDataLink
{
public:
    bool Receive(std::vector<uint8_t> &bytes)
    {
        for (auto b : bytes)
        {
            _txBuffer.push_back(b);
        }

        return true;
    }

    bool SendResponse(std::vector<uint8_t>& data)
    {
        return Transmit(data);
    }

    void Flush()
    {
        _txBuffer.clear();
    }

    std::vector<uint8_t>& GetTxBuffer()
    {
        return _txBuffer;
    }

private:
    std::vector<uint8_t> _txBuffer;
};

class ReadCallback :
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

TEST(IntegrationTest, ReadHolding)
{
    static const uint8_t DEVICEID = 10;
    uint16_t STARTADDRESS = 1337;
    uint16_t COUNT = 3;
    uint16_t VALUES[] = { 123, 234, 456 };

    static const auto FUNCTION = ModbusMaster::Framework::FunctionCode::ReadHolding;

    ReadCallback callback;
    Datalink datalink;
    ModbusMaster::ModbusMaster master(datalink, callback);

    ASSERT_TRUE(master.ReadParameters(DEVICEID, FUNCTION, STARTADDRESS, COUNT));

    auto rx = datalink.GetTxBuffer();
    ASSERT_EQ(rx[0], DEVICEID);
    ASSERT_EQ(rx[1], static_cast<uint8_t>(FUNCTION));
    ASSERT_EQ(rx[2], reinterpret_cast<uint8_t*>(&STARTADDRESS)[1]);
    ASSERT_EQ(rx[3], reinterpret_cast<uint8_t*>(&STARTADDRESS)[0]);
    ASSERT_EQ(rx[4], reinterpret_cast<uint8_t*>(&COUNT)[1]);
    ASSERT_EQ(rx[5], reinterpret_cast<uint8_t*>(&COUNT)[0]);

    datalink.Flush();

    std::vector<uint8_t> response =
    {
        DEVICEID,
        static_cast<uint8_t>(FUNCTION),
        static_cast<uint8_t>(COUNT * 2),
        reinterpret_cast<uint8_t*>(&VALUES[0])[0],
        reinterpret_cast<uint8_t*>(&VALUES[0])[1],
        reinterpret_cast<uint8_t*>(&VALUES[1])[0],
        reinterpret_cast<uint8_t*>(&VALUES[1])[1],
        reinterpret_cast<uint8_t*>(&VALUES[2])[0],
        reinterpret_cast<uint8_t*>(&VALUES[2])[1],
        0,
        0
    };
    ASSERT_TRUE(datalink.SendResponse(response));

    master.Service(0);
}

