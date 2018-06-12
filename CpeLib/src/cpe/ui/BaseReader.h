#pragma once

#include <iostream>
#include <vector>

#include "cpe/tool/text.h"
#include "cpe/ui/output/OutputHelper.h"
#include "cpe/ui/style/TextColor.h"
#include "cpe/ui/BaseElement.h"
#include "IValidator.h"
#include "ReaderResult.h"

namespace cpe {

template<class TDerived, class TValue, class TResult = ReaderResult<TValue>>
class BaseReader : public BaseElement<TDerived> {
public:
    template<class TScript>
    using ResultReadListenerFunc = bool (TScript::*)(TResult &);

    virtual ~BaseReader() { }

    const TextColor &getReadColor() const;

    TextColor &getColorReadRef();

    const std::string &getErrorText() const;

    std::string &getErrorTextRef();

    template<class TValidator>
    void addValidator(const TValidator &validator);

    template<class TValidator>
    void removeValidator(const TValidator &validator);

    // TODO список слушателей
    template<class TScript>
    void addResultReadListener(ResultReadListenerFunc<TScript> func);

    // TODO Удаление слушателя

protected:

    using _PureResultReadListenerFunc  = bool (BaseScript::*)(TResult &);

    _PureResultReadListenerFunc mResultFunc = nullptr;
    std::vector<IValidator<TValue> *> mValidators;
    TextColor mColorRead;
    std::string mErrorText;
    bool fireResultRead(BaseScript &script, TResult &result);

    void run(BaseScript &script) override;

    void onRead(TResult &result);

    virtual bool onConvert(std::string &srcLine, TValue &convertedValue) = 0;

    bool onValidate(const TValue &value, std::vector<std::string> &errorList) const;
};

template<class TDerived, class TValue, class TResult>
const TextColor &BaseReader<TDerived, TValue, TResult>::getReadColor() const {
    return mColorRead;
}

template<class TDerived, class TValue, class TResult>
TextColor &BaseReader<TDerived, TValue, TResult>::getColorReadRef() {
    return mColorRead;
}

template<class TDerived, class TValue, class TResult>
const std::string &BaseReader<TDerived, TValue, TResult>::getErrorText() const {
    return mErrorText;
}

template<class TDerived, class TValue, class TResult>
std::string &BaseReader<TDerived, TValue, TResult>::getErrorTextRef() {
    return mErrorText;
}

template<class TDerived, class TValue, class TResult>
template<class TValidator>
void BaseReader<TDerived, TValue, TResult>::addValidator(const TValidator &validator) {
    mValidators.push_back(static_cast<IValidator<TValue> *>(new TValidator(validator)));
}

template<class TDerived, class TValue, class TResult>
template<class TValidator>
void BaseReader<TDerived, TValue, TResult>::removeValidator(const TValidator &validator) {
    auto finded = std::find(
        mValidators.begin(),
        mValidators.end(),
        static_cast<const IValidator<TValue> *>(&validator));
    if (finded != mValidators.end())
        mValidators.erase(finded);
}

template<class TDerived, class TValue, class TResult>
template<class TScript>
void BaseReader<TDerived, TValue, TResult>::addResultReadListener(ResultReadListenerFunc<TScript> func) {
    mResultFunc = static_cast<_PureResultReadListenerFunc>(func);
}

template<class TDerived, class TValue, class TResult>
bool BaseReader<TDerived, TValue, TResult>::fireResultRead(BaseScript &script, TResult &result) {
    if (mResultFunc)
        return (script.*mResultFunc)(result);
    return true;
}

template<class TDerived, class TValue, class TResult>
void BaseReader<TDerived, TValue, TResult>::run(BaseScript &script) {
    if (!this->getVisible())
        return;

    this->onBeforeRun();
    this->fireBeforeRun(script);

    OutputHelper outHelp;
    outHelp.beginColorize(std::cout);
    while (true) {
        outHelp.saveState();
        outHelp.applyColor(this->getColorReadRef());

        TResult result;
        onRead(result);

        outHelp.resetColor();
        if (fireResultRead(script, result))
            break;
        outHelp.goBackState();
    }
    outHelp.endColorize();

    this->onAfterRun();
}

template<class TDerived, class TValue, class TResult>
void BaseReader<TDerived, TValue, TResult>::onRead(TResult &result) {
    auto &castedResult = static_cast<ReaderResult<TValue> &>(result);

    std::string lineValue;
    std::getline(std::cin, lineValue);
    text::trim(lineValue);

    if (lineValue.empty()) {
        castedResult.assignEmpty();
    } else {
        bool isCommand = (lineValue[0] == '\\');
        if (isCommand || lineValue[0] == '@')
            lineValue.erase(0, 1);

        if (isCommand) {
            castedResult.assignCommand(lineValue);
        } else {
            TValue convertedValue;
            if (onConvert(lineValue, convertedValue)) {
                std::vector<std::string> errorList;
                if (this->onValidate(convertedValue, errorList))
                    castedResult.assignValue(convertedValue);
                else
                    castedResult.assignInvalid(errorList);
            } else {
                castedResult.assignError(this->getErrorTextRef());
            }
        }
    }
}

template<class TDerived, class TValue, class TResult>
bool BaseReader<TDerived, TValue, TResult>::onValidate(const TValue &value, std::vector<std::string> &errorList) const {
    bool totalResult = true;
    for (const IValidator<TValue> *valid : mValidators) {
        if (!valid->validate(value, errorList))
            totalResult = false;
    }
    return totalResult;
}

}




