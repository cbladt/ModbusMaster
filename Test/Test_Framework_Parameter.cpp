#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

#include <Framework/Parameter.hpp>

TEST(Framework_Parameter, Construction)
{
    static const uint16_t ADDRESS = 1337;
    static const ModbusMaster::Framework::ParameterType TYPE = ModbusMaster::Framework::ParameterType::Holding;
    static const uint16_t COUNT = 2;
    static const std::vector<uint8_t> VALUE { 'a', 'b', 'b', 'a' };

    ModbusMaster::Framework::Parameter param(ADDRESS, TYPE, COUNT, VALUE);
    ASSERT_EQ(static_cast<size_t>(COUNT*2), VALUE.size());
    ASSERT_EQ(param.GetAddress(), ADDRESS);
    ASSERT_EQ(param.GetType(), TYPE);
    ASSERT_EQ(param.GetSize(), COUNT);
    ASSERT_EQ(param.GetValue()[0], VALUE[0]);
    ASSERT_EQ(param.GetValue()[1], VALUE[1]);
    ASSERT_EQ(param.GetValue()[2], VALUE[2]);
    ASSERT_EQ(param.GetValue()[3], VALUE[3]);
}

TEST(Framework_Parameter, SetValue)
{
    static const uint16_t ADDRESS = 1337;
    static const ModbusMaster::Framework::ParameterType TYPE = ModbusMaster::Framework::ParameterType::Holding;
    static const uint16_t COUNT = 2;
    static const std::vector<uint8_t> VALUEa { 'a', 'b', 'b', 'a' };
    static const std::vector<uint8_t> VALUEb { 'n', 'e', 'n', 'a' };

    // Initiate with VALUEa, and verify.
    ModbusMaster::Framework::Parameter param(ADDRESS, TYPE, COUNT, VALUEa);
    ASSERT_EQ(static_cast<size_t>(COUNT*2), VALUEa.size());
    ASSERT_EQ(param.GetValue()[0], VALUEa[0]);
    ASSERT_EQ(param.GetValue()[1], VALUEa[1]);
    ASSERT_EQ(param.GetValue()[2], VALUEa[2]);
    ASSERT_EQ(param.GetValue()[3], VALUEa[3]);

    // Set VALUEb, and verify.
    param.Setvalue(VALUEb);
    ASSERT_EQ(static_cast<size_t>(COUNT*2), VALUEb.size());
    ASSERT_EQ(param.GetValue()[0], VALUEb[0]);
    ASSERT_EQ(param.GetValue()[1], VALUEb[1]);
    ASSERT_EQ(param.GetValue()[2], VALUEb[2]);
    ASSERT_EQ(param.GetValue()[3], VALUEb[3]);
}
