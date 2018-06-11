#pragma once

#include <iostream>
#include <vector>

#include "cpe/tool/text.h"
#include "cpe/ui/output/OutputHelper.h"
#include "ReaderData.h"
#include "cpe/ui/BaseElement.h"
#include "IValidator.h"
#include "ReaderResult.h"

namespace cpe {

template<class TValue, class TData = ReaderData<TValue>, class TResult = ReaderResult<TValue>>
class BaseReader : public BaseElement<TData> {

    using _BaseCuiElement = BaseElement<TData>;
public:
    template<class TViewModel>
    using ResultReadReceiverFunc = bool (TViewModel::*)(TResult &);

    virtual ~BaseReader() { }

    template<class TViewModel>
    void bindResult(ResultReadReceiverFunc<TViewModel> func);

    bool fireResult(IController &ctrl, TResult &result);

    void run(IController &ctrl) override;

protected:
    using _PureResultReadReceiverFunc  = bool (IController::*)(TResult &);

    _PureResultReadReceiverFunc mResultFunc = nullptr;

    virtual void onRead(TResult &result);

    virtual bool onConvert(std::string &srcLine, TValue &convertedValue) = 0;
};

template<class TValue, class TData, class TResult>
template<class TViewModel>
void BaseReader<TValue, TData, TResult>::bindResult(BaseReader::ResultReadReceiverFunc<TViewModel> func) {
    mResultFunc = static_cast<_PureResultReadReceiverFunc>(func);
}

template<class TValue, class TData, class TResult>
bool BaseReader<TValue, TData, TResult>::fireResult(IController &ctrl, TResult &result) {
    if (mResultFunc)
        return (ctrl.*mResultFunc)(result);
    return true;
}

template<class TValue, class TData, class TResult>
void BaseReader<TValue, TData, TResult>::run(IController &ctrl) {
    if (!static_cast<IElementData &>(_BaseCuiElement::getData()).getVisible())
        return;

    this->onBeforeRun();
    _BaseCuiElement::fireData(ctrl);
    this->onRun();

    OutputHelper outHelp;
    outHelp.beginColorize(std::cout);
    while (true) {
        outHelp.saveState();
        outHelp.applyColor(
            static_cast<BaseReaderData &>(_BaseCuiElement::getData()).getColorRead());

        TResult result;
        onRead(result);

        outHelp.resetColor();
        if (fireResult(ctrl, result))
            break;
        outHelp.goBackState();
    }
    outHelp.endColorize();

    this->onAfterRun();
}

template<class TValue, class TData, class TResult>
void BaseReader<TValue, TData, TResult>::onRead(TResult &result) {
    auto &castedResult = static_cast<ReaderResult<TValue> &>(result);
    auto &castedData = static_cast<ReaderData<TValue> &>(_BaseCuiElement::getData());

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
                auto errorList = castedData.validate(convertedValue);
                if (errorList.empty())
                    castedResult.assignValue(convertedValue);
                else
                    castedResult.assignInvalid(errorList);
            } else {
                castedResult.assignError(castedData.getErrorText());
            }
        }
    }
}

}




