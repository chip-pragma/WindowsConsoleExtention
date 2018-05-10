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
#include "cpe/ui/write/WriteHelper.h"
#include "IValidator.h"
#include "IConverter.h"

namespace cpe {

template<class TValue>
class Reader : public WriteHelper {
public:
    using ValueType = TValue;

    explicit Reader(const IConverter<TValue> & converter);

    void read(TValue &outValue);

    const Nullable<std::string> &requirement() const;

    Nullable<std::string> &requirement();

    void requirement(const Nullable<std::string> &text);

    const TextCharStyle &read_style() const;

    TextCharStyle &read_style();

    void read_style(const TextCharStyle &readStyle);

    const TextCharStyle &error_style() const;

    TextCharStyle &error_style();

    void error_style(const TextCharStyle &errorStyle);

    template<class TValidator>
    void add_validator(const TValidator &validator);

    template<class TValidator>
    void remove_validator(const TValidator &validator);

private:
    const IConverter<TValue> *mConverter;
    Nullable<std::string> mRequiredText;
    TextCharStyle mReadStyle;
    TextCharStyle mErrorStyle;
    std::vector<const IValidator<TValue> *> mValidators;
};

//region [ definition ]

template<class TValue>
Reader<TValue>::Reader(const IConverter<TValue> &converter) {
    mConverter = &converter;
}

template<class TValue>
const Nullable<std::string> &Reader<TValue>::requirement() const {
    return mRequiredText;
}

template<class TValue>
Nullable<std::string> &Reader<TValue>::requirement() {
    return mRequiredText;
}

template<class TValue>
void Reader<TValue>::requirement(const Nullable<std::string> &text) {
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
        std::string error;

        if (lineValue.empty()) {
            if (mRequiredText.get(error))
                errors.push_back(error);
        } else {
            if (!mConverter->convert(lineValue, convertedValue, error))
                errors.push_back(error);
            else {
                for (const IValidator<TValue> * validator : mValidators)
                    validator->validate(convertedValue, errors);
            }
        }

        if (!errors.empty()) {
            output_apply_style(mErrorStyle);
            for (const auto &err : errors)
                std::cout << err << "\n";
            std::cout.flush();
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
const TextCharStyle &Reader<TValue>::read_style() const {
    return mReadStyle;
}

template<class TValue>
TextCharStyle &Reader<TValue>::read_style() {
    return mReadStyle;
}

template<class TValue>
void Reader<TValue>::read_style(const TextCharStyle &readStyle) {
    mReadStyle = readStyle;
}

template<class TValue>
const TextCharStyle &Reader<TValue>::error_style() const {
    return mErrorStyle;
}

template<class TValue>
TextCharStyle &Reader<TValue>::error_style() {
    return mErrorStyle;
}

template<class TValue>
void Reader<TValue>::error_style(const TextCharStyle &errorStyle) {
    mErrorStyle = errorStyle;
}

template<class TValue>
template<class TValidator>
void Reader<TValue>::add_validator(const TValidator &validator) {
    mValidators.push_back(&validator);
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




