#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

#include "cpe/core/terminal.h"
#include "cpe/core/draw/Point.h"
#include "cpe/core/draw/Color.h"
#include "cpe/tool/text.h"
#include "cpe/tool/Nullable.h"
#include "cpe/ui/style/TextColor.h"
#include "cpe/ui/write/WriteHelper.h"
#include "IValidator.h"
#include "IConverter.h"
#include "ReaderResult.h"

namespace cpe {

template<class TValue>
class Reader : public WriteHelper {
public:
    static constexpr const char *COMMAND_PREFIX = "!:";

    using ValueType = TValue;

    explicit Reader(const IConverter<TValue> &converter);

    ReaderResult<TValue> read();

    const Nullable<std::string> &requirement() const;

    Nullable<std::string> &requirement();

    const TextColor &read_color() const;

    TextColor &read_color();

    const TextColor &error_color() const;

    TextColor &error_color();

    void add_command(uint32_t comId, const std::string &comText);

    void remove_command(uint32_t comId);

    template<class TValidator>
    void add_validator(const TValidator &validator);

    template<class TValidator>
    void remove_validator(const TValidator &validator);

private:
    const IConverter<TValue> *mConverter;
    Nullable<std::string> mRequiredText;
    TextColor mReadStyle;
    TextColor mErrorStyle;
    std::map<uint32_t, std::string> mCommands;
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
ReaderResult<TValue> Reader<TValue>::read() {
    std::string lineValue;
    TValue convertedValue;
    ReaderResult<TValue> result;

    output_begin(std::cout);

    bool breaking = false;
    while (!breaking) {
        state_save();
        output_apply_style(mReadStyle);
        std::getline(std::cin, lineValue);
        text::trim(lineValue);

        ReaderErrorVector errors;
        std::string error;

        if (lineValue.empty()) {
            if (mRequiredText.get(error))
                errors.push_back(error);
        } else {
            if (lineValue.size() > 2 && lineValue.substr(0, 2) == COMMAND_PREFIX) {
                auto command = lineValue.substr(2);
                for (auto it = mCommands.cbegin(); it != mCommands.cend(); ++it) {
                    if (it->second == command)
                        result.set(it->first);
                }
            } else if (!mConverter->convert(lineValue, convertedValue, error))
                errors.push_back(error);
            else {
                for (const IValidator<TValue> *validator : mValidators)
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
                result.set(convertedValue);
            breaking = true;
        }

        output_reset_style();
        state_clear_back();
    }

    output_end();
}

template<class TValue>
const TextColor &Reader<TValue>::read_color() const {
    return mReadStyle;
}

template<class TValue>
TextColor &Reader<TValue>::read_color() {
    return mReadStyle;
}

template<class TValue>
const TextColor &Reader<TValue>::error_color() const {
    return mErrorStyle;
}

template<class TValue>
TextColor &Reader<TValue>::error_color() {
    return mErrorStyle;
}

template<class TValue>
void Reader<TValue>::add_command(uint32_t comId, const std::string &comText) {
    mCommands.insert_or_assign(comId, comText);
}

template<class TValue>
void Reader<TValue>::remove_command(uint32_t comId) {
    mCommands.erase(comId);
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




