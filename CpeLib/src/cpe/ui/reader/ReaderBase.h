#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

#include "cpe/core/terminal.h"
#include "cpe/core/draw/Point.h"
#include "cpe/core/draw/Color.h"
#include "cpe/tool/text.h"
#include "cpe/tool/Nullable.h"
#include "cpe/ui/style/TextColor.h"
#include "cpe/ui/output/OutputHelper.h"
#include "IValidator.h"
#include "IConverter.h"
#include "ResultRead.h"
#include "cpe/ui/writer/IWriter.h"

namespace cpe {

template<class TValue>
class ReaderBase {
public:
    using ValueClass = TValue;

    explicit ReaderBase(const IConverter<TValue> &converter);

    ResultRead<TValue> read();

    const Nullable<std::string> &requirement() const;

    Nullable<std::string> &requirement();

    const TextColor &read_color() const;

    TextColor &read_color();

    void add_command(const std::string &command);

    void remove_command(const std::string &command);

    template<class TValidator>
    void add_validator(const TValidator &validator);

    template<class TValidator>
    void remove_validator(const TValidator &validator);

private:
    const IConverter<TValue> *mConverter;
    Nullable<std::string> mRequiredText;
    TextColor mReadStyle;
    std::set<std::string> mCommands;
    std::vector<const IValidator<TValue> *> mValidators;
};

//region [ definition ]

template<class TValue>
ReaderBase<TValue>::ReaderBase(const IConverter<TValue> &converter) {
    mConverter = &converter;
}

template<class TValue>
const Nullable<std::string> &ReaderBase<TValue>::requirement() const {
    return mRequiredText;
}

template<class TValue>
Nullable<std::string> &ReaderBase<TValue>::requirement() {
    return mRequiredText;
}

template<class TValue>
ResultRead<TValue> ReaderBase<TValue>::read() {
    std::string lineValue;
    TValue convertedValue;
    ResultRead<TValue> result;
    bool notCommand;
    OutputHelper outHelp;

    outHelp.begin_colorized(std::cout);

    bool breaking = false;
    while (!breaking) {
        outHelp.save_state();
        outHelp.apply_color(mReadStyle);
        std::getline(std::cin, lineValue);
        text::trim(lineValue);

        ReaderErrorVector errors;
        std::string error;

        notCommand = (!lineValue.empty() && lineValue[0] == '@');
        if (notCommand)
            lineValue.erase(0, 1);

        if (lineValue.empty()) {
            if (mRequiredText.get(error))
                errors.push_back(error);
        } else {
            if (notCommand) {
                if (!mConverter->convert(lineValue, convertedValue, error))
                    errors.push_back(error);
                else {
                    for (const IValidator<TValue> *validator : mValidators)
                        validator->validate(convertedValue, errors);
                }
            } else {
                for (auto it = mCommands.cbegin();
                     it != mCommands.cend(); ++it) {
                    if (lineValue == *it) {
                        result.assign_command(*it);
                        break;
                    }
                }
            }
        }

        if (!errors.empty()) {
            outHelp.apply_color(mErrorStyle);
            for (const auto &err : errors)
                std::cout << err << "\n";
            std::cout.flush();
            outHelp.reset_colors();
            term::pause();
        } else {
            if (!lineValue.empty() && result.type() == ResultReadType::UNDEFINED)
                result.assign_command(convertedValue);
            breaking = true;
        }

        outHelp.reset_colors();
        outHelp.back_state();
    }

    outHelp.end_colorized();

    return result;
}

template<class TValue>
const TextColor &ReaderBase<TValue>::read_color() const {
    return mReadStyle;
}

template<class TValue>
TextColor &ReaderBase<TValue>::read_color() {
    return mReadStyle;
}

template<class TValue>
void ReaderBase<TValue>::add_command(const std::string &command) {
    mCommands.insert(command);
}

template<class TValue>
void ReaderBase<TValue>::remove_command(const std::string &command) {
    mCommands.erase(command);
}

template<class TValue>
template<class TValidator>
void ReaderBase<TValue>::add_validator(const TValidator &validator) {
    mValidators.push_back(&validator);
}

template<class TValue>
template<class TValidator>
void ReaderBase<TValue>::remove_validator(const TValidator &validator) {
    auto finded = std::find(
            mValidators.cbegin(), mValidators.cend(),
            static_cast<const IValidator<TValue> *>(&validator));
    if (finded != mValidators.cend())
        mValidators.erase(finded);
}

//endregion

}




