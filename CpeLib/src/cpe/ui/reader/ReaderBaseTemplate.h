#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "cpe/tool/text.h"
#include "cpe/ui/style/TextColor.h"
#include "cpe/ui/output/OutputHelper.h"
#include "cpe/ui/InitializerBindingBase.h"
#include "cpe/ui/IInitializer.h"
#include "ResultReadBindingBase.h"
#include "IValidator.h"
#include "IConverter.h"
#include "ResultRead.h"
#include "ReaderBase.h"

namespace cpe {

template<class TValue, class TInitializer, class TResult>
class ReaderBaseTemplate
        : public ReaderBase, public InitializerBindingBase<TInitializer>, public ResultReadBindingBase<TResult> {
    using _InitBinding = InitializerBindingBase<TInitializer>;
    using _ResultBinding = ResultReadBindingBase<TResult>;

public:
    using ValueClass = TValue;

    explicit ReaderBaseTemplate(const IConverter<TValue> &converter);

    template<class TValidator>
    void add_validator(const TValidator &validator);

    template<class TValidator>
    void remove_validator(const TValidator &validator);

    virtual TResult read();

    virtual void on_read(TResult &result);

    void run(IController &ctrl) override;

protected:
    const IConverter<TValue> *mConverter;
    std::vector<const IValidator<TValue> *> mValidators;

    TInitializer make_initializer() override = 0;
};

//region [ definition ]

template<class TValue, class TInitializer, class TResult>
ReaderBaseTemplate<TValue, TInitializer, TResult>::ReaderBaseTemplate(const IConverter<TValue> &converter) {
    mConverter = &converter;
    static_assert(std::is_base_of<TResult, ResultRead<TValue>>::value);
}

template<class TValue, class TInitializer, class TResult>
TResult ReaderBaseTemplate<TValue, TInitializer, TResult>::read() {
    TResult result;
    on_read(result);
    return result;
}

template<class TValue, class TInitializer, class TResult>
void ReaderBaseTemplate<TValue, TInitializer, TResult>::on_read(TResult &result) {
    auto &castedResult = static_cast<ResultRead<TValue> &>(result);

    std::string lineValue;
    std::getline(std::cin, lineValue);
    text::trim(lineValue);

    bool notCommand = (!lineValue.empty() && lineValue[0] == '@');
    if (notCommand)
        lineValue.erase(0, 1);

    if (lineValue.empty()) {
        castedResult.assign_empty();
    } else {
        if (!notCommand) {
            for (auto it = mCommands.cbegin(); it != mCommands.cend(); ++it)
                if (lineValue == *it)
                    castedResult.assign_command(*it);
        }
        if (notCommand || castedResult.type() == ResultReadType::UNDEFINED) {
            TValue convertedValue;
            std::string oneError;
            if (mConverter->convert(lineValue, convertedValue, oneError)) {
                std::vector<std::string> errorList;
                for (const IValidator<TValue> *validator : mValidators)
                    validator->validate(convertedValue, errorList);

                if (errorList.empty())
                    castedResult.assign_value(convertedValue);
                else
                    castedResult.assign_invalid(errorList);
            } else {
                castedResult.assign_convert_fail(oneError);
            }
        }
    }
}

template<class TValue, class TInitializer, class TResult>
void ReaderBaseTemplate<TValue, TInitializer, TResult>::run(IController &ctrl) {
    auto initializer = make_initializer();
    _InitBinding::fire_initializer(ctrl, initializer);

    OutputHelper outHelp;
    outHelp.begin_colorized(std::cout);
    while (true) {
        outHelp.save_state();
        outHelp.apply_color(mReadStyle);


        auto result = read();
        _ResultBinding::fire_result(ctrl, result);
        if (static_cast<ResultRead<TValue>>(result).is_read_applied())
            break;

        outHelp.reset_colors();
        outHelp.back_state();
    }
    outHelp.end_colorized();
}

template<class TValue, class TInitializer, class TResult>
template<class TValidator>
void ReaderBaseTemplate<TValue, TInitializer, TResult>::add_validator(const TValidator &validator) {
    mValidators.push_back(&validator);
}

template<class TValue, class TInitializer, class TResult>
template<class TValidator>
void ReaderBaseTemplate<TValue, TInitializer, TResult>::remove_validator(const TValidator &validator) {
    auto finded = std::find(
            mValidators.cbegin(), mValidators.cend(),
            static_cast<const IValidator<TValue> *>(&validator));
    if (finded != mValidators.cend())
        mValidators.erase(finded);
}

//endregion

}




