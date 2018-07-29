#ifndef FRAMEREQUESTMODEL_HPP
#define FRAMEREQUESTMODEL_HPP

#include <Framework/Frame/IFrame.hpp>

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
        FrameRequestModel(IFrame& frame, size_t expectedReponseDataBytes);

        IFrame& GetFrame() const;

        size_t GetExpectedResponseDataBytes() const;

    private:
        IFrame& _frame;
        size_t _expectedResponseDataBytes;
    };
} // Namespace Frame.
} // Namespace Framewok.
} // Namespace ModbusMaster.

#endif // FRAMEREQUESTMODEL_HPP
