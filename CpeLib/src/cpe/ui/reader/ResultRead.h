#pragma once

#include <cstdint>
#include <variant>

#include "cpe/core/Exception.h"

namespace cpe {

#undef ERROR
enum class ResultReadType : uint8_t {
    UNDEFINED,
    EMPTY,
    COMMAND,
    CONVERT_FAIL,
    INVALID,
    VALUE
};

// TODO закончить с результатом чтения

template<class TValue>
class ResultRead {
public:
    ResultRead() { };

    ResultRead(const ResultRead<TValue> &result);

    ~ResultRead() { };

    void assign_empty();

    void assign_command(const std::string &command);

    void assign_convert_fail(const std::string &error);

    void assign_invalid(const std::vector<std::string>& errors);

    void assign_value(const TValue &value);

    ResultReadType &type() const;

    const std::string &command() const;

    const std::string &convert_fail() const;

    const std::vector<std::string> &invalid() const;

    const TValue &value() const;

private:
    ResultReadType mType = ResultReadType::UNDEFINED;

    std::string mCommand;
    std::string mConvertFail;
    std::vector<std::string> mInvalid;
    TValue mValue;
};

template<class TValue>
ResultRead<TValue>::ResultRead(const ResultRead<TValue> &result) {
    mType = result.mType;
    if (mType == ResultReadType::COMMAND)
        mCommand = result.mCommand;
    else if (mType == ResultReadType::VALUE)
        mValue = result.mValue;
}

template<class TValue>
void ResultRead<TValue>::assign_command(const std::string &command) {
    mType = ResultReadType::COMMAND;
    mCommand = command;
}

template<class TValue>
void ResultRead<TValue>::assign_value(const TValue &value) {
    mType = ResultReadType::VALUE;
    mValue = value;
}

template<class TValue>
ResultReadType &ResultRead<TValue>::type() const {
    return mType;
}

template<class TValue>
const std::string &ResultRead<TValue>::command() const {
    if (mType != ResultReadType::COMMAND)
        throw Exception("Result is not command");
    return mCommand;
}

template<class TValue>
const TValue &ResultRead<TValue>::value() const {
    if (mType != ResultReadType::VALUE)
        throw Exception("Result is not value");
    return mValue;
}

}


