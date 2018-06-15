#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

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
    using ResultReadCallback = bool (TScript::*)(TResult &);

    virtual ~BaseReader() { }

    const TextColor &getReadColor() const;

    TextColor &getColorReadRef();

    const std::string &getErrorText() const;

    std::string &getErrorTextRef();

    template<class TValidator>
    void addValidator(const TValidator &validator);

    template<class TValidator>
    void removeValidator(const TValidator &validator);

    template<class TScript>
    void addResultReadCallback(ResultReadCallback<TScript> func);

    template<class TScript>
    void removeResultReadCallback(ResultReadCallback<TScript> func);

protected:
    std::set<IValidator<TValue> *> mValidators;
    TextColor mColorRead;
    std::string mErrorText;

    bool callResultRead(BaseScript &script, TResult &result);

    void run(BaseScript &script) override;

    void onRead(TResult &result);

    virtual bool onConvert(std::string &srcLine, TValue &convertedValue) = 0;

    bool onValidate(const TValue &value, std::vector<std::string> &errorList) const;

private:
    using _PureResultReadCallback  = bool (BaseScript::*)(TResult &);

    std::vector<_PureResultReadCallback> mResultFuncCallbackVec;
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
    mValidators.insert(static_cast<IValidator<TValue> *>(new TValidator(validator)));
}

template<class TDerived, class TValue, class TResult>
template<class TValidator>
void BaseReader<TDerived, TValue, TResult>::removeValidator(const TValidator &validator) {
    mValidators.erase(&validator);
}

template<class TDerived, class TValue, class TResult>
template<class TScript>
void BaseReader<TDerived, TValue, TResult>::addResultReadCallback(ResultReadCallback<TScript> func) {
    auto castedFunc = static_cast<_PureResultReadCallback>(func);
    bool anyOf = std::any_of(
        mResultFuncCallbackVec.begin(),
        mResultFuncCallbackVec.end(),
        [=](const _PureResultReadCallback& f) {
            return f == castedFunc;
        });
    if (anyOf)
        return;
    mResultFuncCallbackVec.push_back(castedFunc);
}

template<class TDerived, class TValue, class TResult>
template<class TScript>
void BaseReader<TDerived, TValue, TResult>::removeResultReadCallback(BaseReader::ResultReadCallback<TScript> func) {
    auto castedFunc = static_cast<_PureResultReadCallback>(func);
    auto find = std::find(mResultFuncCallbackVec.begin(), mResultFuncCallbackVec.end(), castedFunc);
    if (find != mResultFuncCallbackVec.end())
        mResultFuncCallbackVec.erase(find);
}

template<class TDerived, class TValue, class TResult>
bool BaseReader<TDerived, TValue, TResult>::callResultRead(BaseScript &script, TResult &result) {
    bool callbackResult = true;
    for (auto callback : mResultFuncCallbackVec)
        callbackResult &= (script.*callback)(result);
    return callbackResult;
}

template<class TDerived, class TValue, class TResult>
void BaseReader<TDerived, TValue, TResult>::run(BaseScript &script) {
    this->onBeforeRun();
    this->callBeforeRun(script);

    OutputHelper outHelp;
    outHelp.beginColorize(std::cout);
    while (true) {
        outHelp.saveState();
        outHelp.applyColor(this->getColorReadRef());

        TResult result;
        onRead(result);

        outHelp.resetColor();
        if (callResultRead(script, result))
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




