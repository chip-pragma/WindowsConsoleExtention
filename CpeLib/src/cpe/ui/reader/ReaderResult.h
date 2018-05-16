#pragma once

#include <cstdint>
#include <variant>

#include "cpe/core/Exception.h"

namespace cpe {

#undef ERROR
enum class ReaderResultType : uint8_t {
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

    void set(uint32_t commandId);

    void set(const TValue &value);

    ReaderResultType type() const;

    uint32_t command() const;

    const TValue &value() const;

private:
    ReaderResultType mType = ReaderResultType::ERROR;
    // TODO поработать с Variant
    std::variant<uint32_t, TValue> mResult;
};

template<class TValue>
ReaderResult<TValue>::ReaderResult(const ReaderResult<TValue> &result) {
    mType = result.mType;
    if (mType == ReaderResultType::COMMAND)
        mResult = result.mResult;
    else if (mType == ReaderResultType::VALUE)
        mResult = result.mResult;
}

template<class TValue>
void ReaderResult<TValue>::set(uint32_t commandId) {
    mType = ReaderResultType::COMMAND;
    mResult = commandId;
}

template<class TValue>
void ReaderResult<TValue>::set(const TValue &value) {
    mType = ReaderResultType::VALUE;
    mResult = value;
}

template<class TValue>
ReaderResultType ReaderResult<TValue>::type() const {
    return mType;
}

template<class TValue>
uint32_t ReaderResult<TValue>::command() const {
    if (mType != ReaderResultType::COMMAND)
        throw Exception("Result is not command");
    return std::get<uint32_t>(mResult);
}

template<class TValue>
const TValue &ReaderResult<TValue>::value() const {
    if (mType != ReaderResultType::COMMAND)
        throw Exception("Result is not value");
    return std::get<TValue>(mResult);
}

}


