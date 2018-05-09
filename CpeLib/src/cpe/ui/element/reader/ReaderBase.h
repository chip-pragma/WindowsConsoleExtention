#pragma once

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

#include "cpe/core/terminal.h"
#include "cpe/core/Point.h"
#include "cpe/core/Color.h"
#include "cpe/tool/text.h"
#include "cpe/tool/Nullable.h"
#include "cpe/ui/style/TextCharStyle.h"
#include "cpe/ui/WriteHelper.h"
#include "IValidator.h"

namespace cpe {

template<class TValue>
class ReaderBase {
public:
    using ValueType = TValue;

    virtual bool read(std::string &outValue) = 0;

    bool is_required() const;

    void set_required(bool required);

    bool is_error_ignore() const;

    void set_error_ignore(bool skipError);

    const std::string& get_error_message();

    void set_error_message(const std::string &errorMessage);

    const TextCharStyle &get_read_style() const;

    TextCharStyle &mod_read_style();

    void set_read_style(const TextCharStyle &readStyle);

    const TextCharStyle &get_error_style() const;

    TextCharStyle &mod_error_style();

    void set_error_style(const TextCharStyle &errorStyle);

    template <class TValidator>
    void add_validator(const TValidator &validator);

    template <class TValidator>
    void remove_validator(const TValidator &validator);

protected:
    bool mRequired = false;
    bool mSkipError = false;
    std::string mErrorMessage;
    TextCharStyle mReadStyle;
    TextCharStyle mErrorStyle;

    void validate(const TValue &value, ValidateErrorList &outErrors) const;

private:
    std::list<const IValidator<TValue>*> mValidators;
};

//region [ definition ]

template<class TValue>
bool ReaderBase<TValue>::is_required() const {
    return mRequired;
}

template<class TValue>
void ReaderBase<TValue>::set_required(bool required) {
    mRequired = required;
}

template<class TValue>
bool ReaderBase<TValue>::is_error_ignore() const {
    return mSkipError;
}

template<class TValue>
void ReaderBase<TValue>::set_error_ignore(bool skipError) {
    mSkipError = skipError;
}

template<class TValue>
const std::string &ReaderBase<TValue>::get_error_message() {
    return mErrorMessage;
}

template<class TValue>
void ReaderBase<TValue>::set_error_message(const std::string &errorMessage) {
    mErrorMessage = errorMessage;
}

template<class TValue>
const TextCharStyle &ReaderBase<TValue>::get_read_style() const {
    return mReadStyle;
}

template<class TValue>
TextCharStyle &ReaderBase<TValue>::mod_read_style() {
    return mReadStyle;
}

template<class TValue>
void ReaderBase<TValue>::set_read_style(const TextCharStyle &readStyle) {
    mReadStyle = readStyle;
}

template<class TValue>
const TextCharStyle &ReaderBase<TValue>::get_error_style() const {
    return mErrorStyle;
}

template<class TValue>
TextCharStyle &ReaderBase<TValue>::mod_error_style() {
    return mErrorStyle;
}

template<class TValue>
void ReaderBase<TValue>::set_error_style(const TextCharStyle &errorStyle) {
    mErrorStyle = errorStyle;
}

template<class TValue>
template<class TValidator>
void ReaderBase<TValue>::add_validator(const TValidator &validator) {
    mValidators.push_back(static_cast<const IValidator<TValue>*>(&validator));
}

template<class TValue>
template<class TValidator>
void ReaderBase<TValue>::remove_validator(const TValidator &validator) {
    mValidators.remove(static_cast<const IValidator<TValue>*>(&validator));
}

template<class TValue>
void ReaderBase<TValue>::validate(const TValue &value, ValidateErrorList &outErrors) const {
    for (const IValidator<TValue>* validator : mValidators) {
        validator->operator()(value, outErrors);
    }
}

//endregion

}




