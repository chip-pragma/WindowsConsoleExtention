#pragma once

#include <cstdint>
#include <optional>
#include <vector>
#include <cstdint>

#include "cpe/core/Exception.h"

namespace wce {

enum class ReaderResultType : uint8_t {
    UNDEFINED,
    EMPTY,
    COMMAND,
    CONVERT_FAIL,
    INVALID,
    VALUE
};

template<class TValue>
class ReaderResult {

public:
    ReaderResult() { };

    ~ReaderResult() { };

    void assignEmpty();

    void assignCommand(const std::string &command);

    void assignError(const std::string &error);

    void assignInvalid(const std::vector<std::string> &errors);

    void assignValue(const TValue &value);

    const ReaderResultType &getType() const;

    const std::string &getCommand() const;

    const std::string &getError() const;

    const std::vector<std::string> &getInvalid() const;

    const TValue &getValue() const;

private:
    ReaderResultType mType = ReaderResultType::UNDEFINED;

    std::string mCommand;
    std::string mConvertFail;
    std::vector<std::string> mInvalid;
    TValue mValue;
};

template<class TValue>
void ReaderResult<TValue>::assignEmpty() {
    mType = ReaderResultType::EMPTY;
}

template<class TValue>
void ReaderResult<TValue>::assignCommand(const std::string &command) {
    mCommand = command;
    mType = ReaderResultType::COMMAND;
}

template<class TValue>
void ReaderResult<TValue>::assignError(const std::string &error) {
    mConvertFail = error;
    mType = ReaderResultType::CONVERT_FAIL;
}

template<class TValue>
void ReaderResult<TValue>::assignInvalid(const std::vector<std::string> &errors) {
    mInvalid = errors;
    mType = ReaderResultType::INVALID;
}

template<class TValue>
void ReaderResult<TValue>::assignValue(const TValue &value) {
    mValue = value;
    mType = ReaderResultType::VALUE;
}

template<class TValue>
const ReaderResultType &ReaderResult<TValue>::getType() const {
    return mType;
}

template<class TValue>
const std::string &ReaderResult<TValue>::getCommand() const {
    if (mType != ReaderResultType::COMMAND)
        throw Exception("Result is not <command>");
    return mCommand;
}

template<class TValue>
const std::string &ReaderResult<TValue>::getError() const {
    if (mType != ReaderResultType::CONVERT_FAIL)
        throw Exception("Result is not <convert fail>");
    return mConvertFail;
}

template<class TValue>
const std::vector<std::string> &ReaderResult<TValue>::getInvalid() const {
    if (mType != ReaderResultType::INVALID)
        throw Exception("Result is not <invalid>");
    return mInvalid;
}

template<class TValue>
const TValue &ReaderResult<TValue>::getValue() const {
    if (mType != ReaderResultType::VALUE)
        throw Exception("Result is not <value>");
    return mValue;
}

}


