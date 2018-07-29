#include "FrameRequestModel.hpp"

namespace ModbusMaster
{
namespace Framework
{
namespace Frame
{
    FrameRequestModel::FrameRequestModel(IFrame &frame, size_t expectedReponseDataBytes) :
        _frame(frame),
        _expectedResponseDataBytes(expectedReponseDataBytes)
    {}

    IFrame& FrameRequestModel::GetFrame() const
    {
        return _frame;
    }

    size_t FrameRequestModel::GetExpectedResponseDataBytes() const
    {
        return _expectedResponseDataBytes;
    }
} // Namespace Frame.
} // Namespace Framework.
} // Namespace ModbusMaster.

