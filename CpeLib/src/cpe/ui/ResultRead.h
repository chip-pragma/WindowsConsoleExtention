#pragma once

#include <cstdint>
#include <variant>

#include "cpe/core/Exception.h"

namespace cpe {

#undef ERROR
enum class ResultReadType : uint8_t {
    UNDEFINED,
    ERROR,
    COMMAND,
    VALUE
};

template<class TValue>
class ResultRead {
public:
    ResultRead() { };

    ResultRead(const ResultRead<TValue> &result);

    ~ResultRead() { };

    void set(const std::string &command);

    void set(const TValue &value);

    ResultReadType type() const;

    const std::string &command() const;

    const TValue &value() const;

private:
    ResultReadType mType = ResultReadType::ERROR;
    union {
        TValue mValue;
        std::string mCommand;
    };
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
void ResultRead<TValue>::set(const std::string &command) {
    mType = ResultReadType::COMMAND;
    mCommand = command;
}

template<class TValue>
void ResultRead<TValue>::set(const TValue &value) {
    mType = ResultReadType::VALUE;
    mValue = value;
}

template<class TValue>
ResultReadType ResultRead<TValue>::type() const {
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


