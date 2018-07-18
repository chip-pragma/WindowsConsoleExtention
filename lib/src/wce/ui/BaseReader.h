#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include "wce/tool/text.h"
#include "wce/ui/output/OutputHelper.h"
#include "wce/ui/style/TextColor.h"
#include "wce/ui/BaseElement.h"
#include "wce/core/Event.h"
#include "IValidator.h"
#include "ReaderResult.h"

namespace wce {

template<class TDerived, class TValue, class TResult = ReaderResult<TValue>>
class BaseReader : public BaseElement<TDerived> {
    using Type = BaseReader<TDerived, TValue, TResult>;
public:
//    template<class TScript>
//    using ResultReadCallback = bool (TScript::*)(TResult &);

    // TODO закончить с EventArgs
    Event<Type, TDerived&, TResult&> eventValueRead;
    Event<Type, TDerived&, TResult&> eventCommandRead;
    Event<Type, TDerived&, TResult&> eventErrorRead;

    TextColor color;
    std::string errorText;

    virtual ~BaseReader() { }

    template<class TValidator>
    void addValidator(const TValidator &validator);

    template<class TValidator>
    void removeValidator(const TValidator &validator);

//    template<class TScript>
//    void addResultReadCallback(ResultReadCallback<TScript> func);
//
//    template<class TScript>
//    void removeResultReadCallback(ResultReadCallback<TScript> func);

protected:
    std::set<IValidator<TValue> *> m_validators;

//    bool callResultRead(BaseScript &script, TResult &result);

    void run(BaseScript &script) override;

    void onRead(TResult &result);

    virtual bool onConvert(std::string &srcLine, TValue &convertedValue) = 0;

    bool onValidate(const TValue &value, std::vector<std::string> &errorList) const;

private:
//    using _PureResultReadCallback  = bool (BaseScript::*)(TResult &);
//
//    std::vector<_PureResultReadCallback> m_resultFuncCallbackVec;
};

template<class TDerived, class TValue, class TResult>
template<class TValidator>
void BaseReader<TDerived, TValue, TResult>::addValidator(const TValidator &validator) {
    m_validators.insert(static_cast<IValidator<TValue> *>(new TValidator(validator)));
}

template<class TDerived, class TValue, class TResult>
template<class TValidator>
void BaseReader<TDerived, TValue, TResult>::removeValidator(const TValidator &validator) {
    m_validators.erase(&validator);
}

//template<class TDerived, class TValue, class TResult>
//template<class TScript>
//void BaseReader<TDerived, TValue, TResult>::addResultReadCallback(ResultReadCallback<TScript> func) {
//    auto castedFunc = static_cast<_PureResultReadCallback>(func);
//    bool anyOf = std::any_of(
//        m_resultFuncCallbackVec.begin(),
//        m_resultFuncCallbackVec.end(),
//        [=](const _PureResultReadCallback& f) {
//            return f == castedFunc;
//        });
//    if (anyOf)
//        return;
//    m_resultFuncCallbackVec.push_back(castedFunc);
//}
//
//template<class TDerived, class TValue, class TResult>
//template<class TScript>
//void BaseReader<TDerived, TValue, TResult>::removeResultReadCallback(BaseReader::ResultReadCallback<TScript> func) {
//    auto castedFunc = static_cast<_PureResultReadCallback>(func);
//    auto find = std::find(m_resultFuncCallbackVec.begin(), m_resultFuncCallbackVec.end(), castedFunc);
//    if (find != m_resultFuncCallbackVec.end())
//        m_resultFuncCallbackVec.erase(find);
//}

//template<class TDerived, class TValue, class TResult>
//bool BaseReader<TDerived, TValue, TResult>::callResultRead(BaseScript &script, TResult &result) {
//    bool callbackResult = true;
//    for (auto callback : m_resultFuncCallbackVec)
//        callbackResult &= (script.*callback)(result);
//    return callbackResult;
//}

template<class TDerived, class TValue, class TResult>
void BaseReader<TDerived, TValue, TResult>::run(BaseScript &script) {
    this->onBeforeRun();

    OutputHelper outHelp;
    outHelp.beginColorize(std::cout);
    while (true) {
        outHelp.saveState();
        outHelp.applyColor(this->color);

        TResult result;
        onRead(result);

        outHelp.resetColor();
        // TODO результат принятия считанного значения передавать в ResultRead

        if (callResultRead(script, ))
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
                    castedResult.assignValidateFail(errorList);
            } else {
                castedResult.assignConvertFail(this->errorText);
            }
        }
    }

    this->eventValueRead.invoke(*this, result);
}

template<class TDerived, class TValue, class TResult>
bool BaseReader<TDerived, TValue, TResult>::onValidate(const TValue &value, std::vector<std::string> &errorList) const {
    bool totalResult = true;
    for (const IValidator<TValue> *valid : m_validators) {
        if (!valid->validate(value, errorList))
            totalResult = false;
    }
    return totalResult;
}

}




