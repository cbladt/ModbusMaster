#ifndef FRAMEREQUESTMODEL_HPP
#define FRAMEREQUESTMODEL_HPP

#include <Framework/Frame/IFrame.hpp>
#include <Framework/Frame/FrameContent.hpp>
#include <Framework/IReceive.hpp>

#include <cstddef>

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    class FrameRequestModel
    {
    public:
        FrameRequestModel(IFrame& frame, Framework::IReceive<FrameContent>& callback, size_t expectedReponseDataBytes);
        ~FrameRequestModel() = default;

        IFrame& GetFrame() const;

        Framework::IReceive<FrameContent>& GetCallback() const;

        size_t GetExpectedResponseDataBytes() const;

    private:
        IFrame& _frame;
        Framework::IReceive<FrameContent>& _callback;
        size_t _expectedResponseDataBytes;
    };
} // Namespace Frame.
} // Namespace Framewok.
} // Namespace ModbusMaster.

#endif // FRAMEREQUESTMODEL_HPP
