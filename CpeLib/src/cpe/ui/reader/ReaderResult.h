#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include "cpe/core/Exception.h"

namespace cpe {

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

    void assign_empty();

    void assign_command(const std::string &command);

    void assign_convert_fail(const std::string &error);

    void assign_invalid(const std::vector<std::string> &errors);

    void assign_value(const TValue &value);

    const ReaderResultType &type() const;

    void applied_read(bool apply);

    bool is_read_applied() const;

    const std::string &command() const;

    const std::string &convert_fail() const;

    const std::vector<std::string> &invalid() const;

    const TValue &value() const;

private:
    ReaderResultType mType = ReaderResultType::UNDEFINED;
    bool mReadApplied;

    std::string mCommand;
    std::string mConvertFail;
    std::vector<std::string> mInvalid;
    TValue mValue;
};

template<class TValue>
void ReaderResult<TValue>::assign_empty() {
    mType = ReaderResultType::EMPTY;
}

template<class TValue>
void ReaderResult<TValue>::assign_command(const std::string &command) {
    mCommand = command;
    mType = ReaderResultType::COMMAND;
}

template<class TValue>
void ReaderResult<TValue>::assign_convert_fail(const std::string &error) {
    mConvertFail = error;
    mType = ReaderResultType::CONVERT_FAIL;
}

template<class TValue>
void ReaderResult<TValue>::assign_invalid(const std::vector<std::string> &errors) {
    mInvalid = errors;
    mType = ReaderResultType::INVALID;
}

template<class TValue>
void ReaderResult<TValue>::assign_value(const TValue &value) {
    mValue = value;
    mType = ReaderResultType::VALUE;
}

template<class TValue>
const ReaderResultType &ReaderResult<TValue>::type() const {
    return mType;
}

template<class TValue>
void ReaderResult<TValue>::applied_read(bool apply) {
    mReadApplied = apply;
}

template<class TValue>
bool ReaderResult<TValue>::is_read_applied() const {
    return mReadApplied;
}

template<class TValue>
const std::string &ReaderResult<TValue>::command() const {
    if (mType != ReaderResultType::COMMAND)
        throw Exception("Result is not <command>");
    return mCommand;
}

template<class TValue>
const std::string &ReaderResult<TValue>::convert_fail() const {
    if (mType != ReaderResultType::CONVERT_FAIL)
        throw Exception("Result is not <convert fail>");
    return mConvertFail;
}

template<class TValue>
const std::vector<std::string> &ReaderResult<TValue>::invalid() const {
    if (mType != ReaderResultType::INVALID)
        throw Exception("Result is not <invalid>");
    return mInvalid;
}

template<class TValue>
const TValue &ReaderResult<TValue>::value() const {
    if (mType != ReaderResultType::VALUE)
        throw Exception("Result is not value");
    return mValue;
}

}


