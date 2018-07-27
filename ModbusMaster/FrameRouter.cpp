#include "FrameRouter.hpp"

namespace ModbusMaster
{
    FrameRouter::FrameRouter()
    {}

    bool FrameRouter::Receive(RequestModel &data)
    {
        switch (data.GetFunctionCode())
        {
            case Framework::FunctionCode::ReadHolding:
                return _readHoldingSubject.Transmit(data);
            case Framework::FunctionCode::ReadInput:
                return _readInputSubject.Transmit(data);
            case Framework::FunctionCode::WriteMultiple:
                return _writeMultipleSubject.Transmit(data);
            default:
                return false;
        }
    }

    Framework::TransmitBase<RequestModel>& FrameRouter::GetReadInputSubject()
    {
        return _readInputSubject;
    }

    Framework::TransmitBase<RequestModel>& FrameRouter::GetReadHoldingSubject()
    {
        return _readHoldingSubject;
    }

    Framework::TransmitBase<RequestModel>& FrameRouter::GetWriteMutipleSubject()
    {
        return _writeMultipleSubject;
    }
} // Namespace ModbusMaster.
