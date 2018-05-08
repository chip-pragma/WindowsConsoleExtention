#pragma once

#include <iostream>
#include <string>

#include "cpe/core/terminal.h"
#include "cpe/core/Point.h"
#include "cpe/core/Color.h"
#include "cpe/tool/text.h"
#include "cpe/tool/Nullable.h"
#include "cpe/ui/style/TextCharStyle.h"
#include "cpe/ui/WriteHelper.h"

namespace cpe {

template<class TValue>
class ReaderAbstract {
public:
    using ValueType = TValue;

    virtual void read(ValueType& valueRead) = 0;

    void set_required(bool required);

    bool is_required() const;

    void set_skip_error(bool skipError);

    bool is_skip_error() const;

    const std::string& error_message();

    void error_message(const std::string& errorMessage);

    const Nullable<TextCharStyle> &read_style() const;

    void read_style(const Nullable<TextCharStyle> &readStyle);

    const Nullable<TextCharStyle> &error_style() const;

    void error_style(const Nullable<TextCharStyle> &errorStyle);

private:
    bool mRequired = false;
    bool mSkipError = false;
    std::string mErrorMessage;
    Nullable<TextCharStyle> mReadStyle;
    Nullable<TextCharStyle> mErrorStyle;
};

template<class TValue>
void ReaderAbstract<TValue>::set_required(bool required) {
    mRequired = required;
}

template<class TValue>
bool ReaderAbstract<TValue>::is_required() const {
    return mRequired;
}

template<class TValue>
void ReaderAbstract<TValue>::set_skip_error(bool skipError) {
    mSkipError = skipError;
}

template<class TValue>
bool ReaderAbstract<TValue>::is_skip_error() const {
    return mSkipError;
}

template<class TValue>
const std::string &ReaderAbstract<TValue>::error_message() {
    return mErrorMessage;
}

template<class TValue>
void ReaderAbstract<TValue>::error_message(const std::string &errorMessage) {
    mErrorMessage = errorMessage;
}

template<class TValue>
const Nullable<TextCharStyle> &ReaderAbstract<TValue>::read_style() const {
    return mReadStyle;
}

template<class TValue>
void ReaderAbstract<TValue>::read_style(const Nullable<TextCharStyle> &readStyle) {
    mReadStyle.set(readStyle);
}

template<class TValue>
const Nullable<TextCharStyle> &ReaderAbstract<TValue>::error_style() const {
    return mErrorStyle;
}

template<class TValue>
void ReaderAbstract<TValue>::error_style(const Nullable<TextCharStyle> &errorStyle) {
    mErrorStyle.set(errorStyle);
}

}




