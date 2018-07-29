#ifndef FRAMEREQUESTMODEL_HPP
#define FRAMEREQUESTMODEL_HPP

#include <Framework/Frame/IFrame.hpp>
#include <Framework/IReceive.hpp>

#include <cstddef>
#include <vector>

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    class FrameRequestModel
    {
    public:
        FrameRequestModel(IFrame& frame, Framework::IReceive<std::vector<uint8_t>>& callback, size_t expectedReponseDataBytes);

        IFrame& GetFrame() const;

        Framework::IReceive<std::vector<uint8_t>>& GetCallback() const;

        size_t GetExpectedResponseDataBytes() const;

    private:
        IFrame& _frame;
        Framework::IReceive<std::vector<uint8_t>>& _callback;
        size_t _expectedResponseDataBytes;
    };
} // Namespace Frame.
} // Namespace Framewok.
} // Namespace ModbusMaster.

#endif // FRAMEREQUESTMODEL_HPP
