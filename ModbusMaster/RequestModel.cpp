#include "RequestModel.hpp"

namespace ModbusMaster
{
    RequestModel::RequestModel(uint8_t device, Framework::FunctionCode functionCode, const std::vector<Framework::Parameter> &parameters) :
        _device(device),
        _functionCode(functionCode),
        _parameters(parameters)
    {}

    uint8_t RequestModel::GetDevice() const
    {
        return _device;
    }

    Framework::FunctionCode RequestModel::GetFunctionCode() const
    {
        return _functionCode;
    }

    const std::vector<Framework::Parameter>& RequestModel::GetParameters() const
    {
        return _parameters;
    }
} // Namespace ModbusMaster.
