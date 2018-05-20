#pragma once

#include <cstdint>
#include <optional>

#include "cpe/core/Exception.h"

namespace cpe {

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

    ~ResultRead() { };

    void assign_empty();

    void assign_command(const std::string &command);

    void assign_convert_fail(const std::string &error);

    void assign_invalid(const std::vector<std::string> &errors);

    void assign_value(const TValue &value);

    const ResultReadType &type() const;

    void applied_read(bool apply);

    bool is_read_applied() const;

    const std::string &command() const;

    const std::string &convert_fail() const;

    const std::vector<std::string> &invalid() const;

    const TValue &value() const;

private:
    ResultReadType mType = ResultReadType::UNDEFINED;
    bool mReadApplied;

    std::string mCommand;
    std::string mConvertFail;
    std::vector<std::string> mInvalid;
    TValue mValue;
};

template<class TValue>
void ResultRead<TValue>::assign_empty() {
    mType = ResultReadType::EMPTY;
}

template<class TValue>
void ResultRead<TValue>::assign_command(const std::string &command) {
    mCommand = command;
    mType = ResultReadType::COMMAND;
}

template<class TValue>
void ResultRead<TValue>::assign_convert_fail(const std::string &error) {
    mConvertFail = error;
    mType = ResultReadType::CONVERT_FAIL;
}

template<class TValue>
void ResultRead<TValue>::assign_invalid(const std::vector<std::string> &errors) {
    mInvalid = errors;
    mType = ResultReadType::INVALID;
}

template<class TValue>
void ResultRead<TValue>::assign_value(const TValue &value) {
    mValue = value;
    mType = ResultReadType::VALUE;
}

template<class TValue>
const ResultReadType &ResultRead<TValue>::type() const {
    return mType;
}

template<class TValue>
void ResultRead<TValue>::applied_read(bool apply) {
    mReadApplied = apply;
}

template<class TValue>
bool ResultRead<TValue>::is_read_applied() const {
    return mReadApplied;
}

template<class TValue>
const std::string &ResultRead<TValue>::command() const {
    if (mType != ResultReadType::COMMAND)
        throw Exception("Result is not <command>");
    return mCommand;
}

template<class TValue>
const std::string &ResultRead<TValue>::convert_fail() const {
    if (mType != ResultReadType::CONVERT_FAIL)
        throw Exception("Result is not <convert fail>");
    return mConvertFail;
}

template<class TValue>
const std::vector<std::string> &ResultRead<TValue>::invalid() const {
    if (mType != ResultReadType::INVALID)
        throw Exception("Result is not <invalid>");
    return mInvalid;
}

template<class TValue>
const TValue &ResultRead<TValue>::value() const {
    if (mType != ResultReadType::VALUE)
        throw Exception("Result is not value");
    return mValue;
}

}


