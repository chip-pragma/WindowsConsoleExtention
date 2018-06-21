#pragma once

#include <cstdint>
#include <optional>
#include <vector>
#include <cstdint>

#include "wce/core/Exception.h"

namespace wce {

enum class ReaderResultState : uint8_t {
    UNDEFINED,
    EMPTY_READ,
    COMMAND_READ,
    CONVERT_FAIL,
    VALIDATE_FAIL,
    VALUE_READ
};

template<class TValue>
class ReaderResult {

public:
    ReaderResult() { };

    ~ReaderResult() { };

    void assignEmpty();

    void assignCommand(const std::string &command);

    void assignConvertFail(const std::string &error);

    void assignValidateFail(const std::vector<std::string> &errors);

    void assignValue(const TValue &value);

    const ReaderResultState &getState() const;

    const std::string &getCommand() const;

    const std::string &getConvertFail() const;

    const std::vector<std::string> &getValidateFail() const;

    const TValue &getValue() const;

private:
    ReaderResultState m_type = ReaderResultState::UNDEFINED;

    std::string m_command;
    std::string m_convertFail;
    std::vector<std::string> m_invalid;
    TValue m_value;
};

template<class TValue>
void ReaderResult<TValue>::assignEmpty() {
    m_type = ReaderResultState::EMPTY_READ;
}

template<class TValue>
void ReaderResult<TValue>::assignCommand(const std::string &command) {
    m_command = command;
    m_type = ReaderResultState::COMMAND_READ;
}

template<class TValue>
void ReaderResult<TValue>::assignConvertFail(const std::string &error) {
    m_convertFail = error;
    m_type = ReaderResultState::CONVERT_FAIL;
}

template<class TValue>
void ReaderResult<TValue>::assignValidateFail(const std::vector<std::string> &errors) {
    m_invalid = errors;
    m_type = ReaderResultState::VALIDATE_FAIL;
}

template<class TValue>
void ReaderResult<TValue>::assignValue(const TValue &value) {
    m_value = value;
    m_type = ReaderResultState::VALUE_READ;
}

template<class TValue>
const ReaderResultState &ReaderResult<TValue>::getState() const {
    return m_type;
}

template<class TValue>
const std::string &ReaderResult<TValue>::getCommand() const {
    if (m_type != ReaderResultState::COMMAND_READ)
        throw Exception("Result is not <command>");
    return m_command;
}

template<class TValue>
const std::string &ReaderResult<TValue>::getConvertFail() const {
    if (m_type != ReaderResultState::CONVERT_FAIL)
        throw Exception("Result is not <convert fail>");
    return m_convertFail;
}

template<class TValue>
const std::vector<std::string> &ReaderResult<TValue>::getValidateFail() const {
    if (m_type != ReaderResultState::VALIDATE_FAIL)
        throw Exception("Result is not <invalid>");
    return m_invalid;
}

template<class TValue>
const TValue &ReaderResult<TValue>::getValue() const {
    if (m_type != ReaderResultState::VALUE_READ)
        throw Exception("Result is not <value>");
    return m_value;
}

}


