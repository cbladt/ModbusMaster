#include "FrameRequestModel.hpp"

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    FrameRequestModel::FrameRequestModel(IFrame &frame, Framework::IReceive<FrameContent>& callback, size_t expectedReponseDataBytes) :
        _frame(frame),
        _callback(callback),
        _expectedResponseDataBytes(expectedReponseDataBytes)
    {}

    IFrame& FrameRequestModel::GetFrame() const
    {
        return _frame;
    }

    Framework::IReceive<FrameContent>& FrameRequestModel::GetCallback() const
    {
        return _callback;
    }

    size_t FrameRequestModel::GetExpectedResponseDataBytes() const
    {
        return _expectedResponseDataBytes;
    }
} // Namespace Frame.
} // Namespace Framework.
} // Namespace ModbusMaster.

