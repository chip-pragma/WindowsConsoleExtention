#pragma once

#include <cstdint>
#include <optional>
#include <vector>
#include <cstdint>

#include "wce/core/Exception.h"

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
    ReaderResultType m_type = ReaderResultType::UNDEFINED;

    std::string m_command;
    std::string m_convertFail;
    std::vector<std::string> m_invalid;
    TValue m_value;
};

template<class TValue>
void ReaderResult<TValue>::assignEmpty() {
    m_type = ReaderResultType::EMPTY;
}

template<class TValue>
void ReaderResult<TValue>::assignCommand(const std::string &command) {
    m_command = command;
    m_type = ReaderResultType::COMMAND;
}

template<class TValue>
void ReaderResult<TValue>::assignError(const std::string &error) {
    m_convertFail = error;
    m_type = ReaderResultType::CONVERT_FAIL;
}

template<class TValue>
void ReaderResult<TValue>::assignInvalid(const std::vector<std::string> &errors) {
    m_invalid = errors;
    m_type = ReaderResultType::INVALID;
}

template<class TValue>
void ReaderResult<TValue>::assignValue(const TValue &value) {
    m_value = value;
    m_type = ReaderResultType::VALUE;
}

template<class TValue>
const ReaderResultType &ReaderResult<TValue>::getType() const {
    return m_type;
}

template<class TValue>
const std::string &ReaderResult<TValue>::getCommand() const {
    if (m_type != ReaderResultType::COMMAND)
        throw Exception("Result is not <command>");
    return m_command;
}

template<class TValue>
const std::string &ReaderResult<TValue>::getError() const {
    if (m_type != ReaderResultType::CONVERT_FAIL)
        throw Exception("Result is not <convert fail>");
    return m_convertFail;
}

template<class TValue>
const std::vector<std::string> &ReaderResult<TValue>::getInvalid() const {
    if (m_type != ReaderResultType::INVALID)
        throw Exception("Result is not <invalid>");
    return m_invalid;
}

template<class TValue>
const TValue &ReaderResult<TValue>::getValue() const {
    if (m_type != ReaderResultType::VALUE)
        throw Exception("Result is not <value>");
    return m_value;
}

}


