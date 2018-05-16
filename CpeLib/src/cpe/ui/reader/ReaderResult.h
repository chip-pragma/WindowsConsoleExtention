#pragma once

#include <cstdint>
#include <variant>

#include "cpe/core/Exception.h"

namespace cpe {

#undef ERROR
enum class ReaderResultType : uint8_t {
    UNDEFINED,
    ERROR,
    COMMAND,
    VALUE
};

template<class TValue>
class ReaderResult {
public:
    ReaderResult() { };

    ReaderResult(const ReaderResult<TValue> &result);

    ~ReaderResult() { };

    void set(const std::string &command);

    void set(const TValue &value);

    ReaderResultType type() const;

    const std::string &command() const;

    const TValue &value() const;

private:
    ReaderResultType mType = ReaderResultType::ERROR;
    union {
        TValue mValue;
        std::string mCommand;
    };
};

template<class TValue>
ReaderResult<TValue>::ReaderResult(const ReaderResult<TValue> &result) {
    mType = result.mType;
    if (mType == ReaderResultType::COMMAND)
        mCommand = result.mCommand;
    else if (mType == ReaderResultType::VALUE)
        mValue = result.mValue;
}

template<class TValue>
void ReaderResult<TValue>::set(const std::string &command) {
    mType = ReaderResultType::COMMAND;
    mCommand = command;
}

template<class TValue>
void ReaderResult<TValue>::set(const TValue &value) {
    mType = ReaderResultType::VALUE;
    mValue = value;
}

template<class TValue>
ReaderResultType ReaderResult<TValue>::type() const {
    return mType;
}

template<class TValue>
const std::string &ReaderResult<TValue>::command() const {
    if (mType != ReaderResultType::COMMAND)
        throw Exception("Result is not command");
    return mCommand;
}

template<class TValue>
const TValue &ReaderResult<TValue>::value() const {
    if (mType != ReaderResultType::VALUE)
        throw Exception("Result is not value");
    return mValue;
}

}


