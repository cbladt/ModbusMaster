#ifndef REQUESTMODEL_HPP
#define REQUESTMODEL_HPP

#include <Framework/FunctionCode.hpp>
#include <Framework/Parameter.hpp>

#include <vector>

namespace ModbusMaster
{
    class RequestModel
    {
    public:
        RequestModel(uint8_t device, Framework::FunctionCode functionCode, const std::vector<Framework::Parameter>& parameters);

        uint8_t GetDevice() const;

        Framework::FunctionCode GetFunctionCode() const;

        const std::vector<Framework::Parameter>& GetParameters() const;

    private:
        uint8_t _device;
        Framework::FunctionCode _functionCode;
        const std::vector<Framework::Parameter>& _parameters;
    };
} // Namespace ModbusMaster.

#endif // REQUESTMODEL_HPP
