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
#include "ConverterBase.h"

namespace cpe {

template<class TValue>
class Reader : public WriteHelper {
public:
    explicit Reader(const ConverterBase<TValue> &converter);

    using ValueType = TValue;

    void read(TValue &outValue);

    const Nullable<std::string> &get_required() const;

    Nullable<std::string> &mod_required();

    void set_required(const Nullable<std::string> &text);

    const TextCharStyle &get_read_style() const;

    TextCharStyle &mod_read_style();

    void set_read_style(const TextCharStyle &readStyle);

    const TextCharStyle &get_error_style() const;

    TextCharStyle &mod_error_style();

    void set_error_style(const TextCharStyle &errorStyle);

    template<class TValidator>
    void add_validator(const TValidator &validator);

    template<class TValidator>
    void remove_validator(const TValidator &validator);

private:
    const ConverterBase<TValue> *mConverter;
    Nullable<std::string> mRequiredText;
    TextCharStyle mReadStyle;
    TextCharStyle mErrorStyle;
    std::vector<const IValidator<TValue> *> mValidators;
};

//region [ definition ]

template<class TValue>
Reader<TValue>::Reader(const ConverterBase<TValue> &converter) {
    mConverter = &converter;
}

template<class TValue>
const Nullable<std::string> &Reader<TValue>::get_required() const {
    return mRequiredText;
}

template<class TValue>
Nullable<std::string> &Reader<TValue>::mod_required() {
    return mRequiredText;
}

template<class TValue>
void Reader<TValue>::set_required(const Nullable<std::string> &text) {
    mRequiredText = text;
}

template<class TValue>
void Reader<TValue>::read(TValue &outValue) {

    std::string lineValue;
    TValue convertedValue;

    output_begin(std::cout);

    bool breaking = false;
    while (!breaking) {
        state_save();
        output_apply_style(mReadStyle);
        std::getline(std::cin, lineValue);

        ReaderErrorVector errors;

        if (lineValue.empty()) {
            std::string error;
            if (mRequiredText.get(error))
                errors.push_back(error);
        } else {
            if (!mConverter->operator()(lineValue, convertedValue))
                errors.push_back(mConverter->get_error_text());
            else
                for (const IValidator<TValue> *validator : mValidators)
                    validator->operator()(convertedValue, errors);
        }

        if (!errors.empty()) {
            output_apply_style(mErrorStyle);
            errors.output();
            output_reset_style();
            term::pause();
        } else {
            if (!lineValue.empty())
                outValue = convertedValue;
            breaking = true;
        }

        output_reset_style();
        state_clear_back();
    }

    output_end();
}

template<class TValue>
const TextCharStyle &Reader<TValue>::get_read_style() const {
    return mReadStyle;
}

template<class TValue>
TextCharStyle &Reader<TValue>::mod_read_style() {
    return mReadStyle;
}

template<class TValue>
void Reader<TValue>::set_read_style(const TextCharStyle &readStyle) {
    mReadStyle = readStyle;
}

template<class TValue>
const TextCharStyle &Reader<TValue>::get_error_style() const {
    return mErrorStyle;
}

template<class TValue>
TextCharStyle &Reader<TValue>::mod_error_style() {
    return mErrorStyle;
}

template<class TValue>
void Reader<TValue>::set_error_style(const TextCharStyle &errorStyle) {
    mErrorStyle = errorStyle;
}

template<class TValue>
template<class TValidator>
void Reader<TValue>::add_validator(const TValidator &validator) {
    mValidators.push_back(static_cast<const IValidator<TValue> *>(&validator));
}

template<class TValue>
template<class TValidator>
void Reader<TValue>::remove_validator(const TValidator &validator) {
    auto finded = std::find(
            mValidators.cbegin(), mValidators.cend(),
            static_cast<const IValidator<TValue> *>(&validator));
    if (finded != mValidators.cend())
        mValidators.erase(finded);
}

//endregion

}




