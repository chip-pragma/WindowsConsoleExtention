#pragma once

#include <iostream>
#include <vector>

#include "cpe/tool/text.h"
#include "cpe/ui/output/OutputHelper.h"
#include "ReaderData.h"
#include "cpe/ui/BaseCuiElement.h"
#include "IValidator.h"
#include "ReaderResult.h"

namespace cpe {

template<class TValue, class TData = ReaderData<TValue>, class TResult = ReaderResult<TValue>>
class BaseReader : public BaseCuiElement<TData> {

    using _BaseCuiElement = BaseCuiElement<TData>;
public:
    template<class TViewModel>
    using ResultReadReceiverFunc = bool (TViewModel::*)(TResult &);

    virtual ~BaseReader() { }

    template<class TViewModel>
    void bind_result(ResultReadReceiverFunc<TViewModel> func);

    bool fire_result(IViewModel &ctrl, TResult &result);

    void run(IViewModel &ctrl) override;

protected:
    using _PureResultReadReceiverFunc  = bool (IViewModel::*)(TResult &);

    _PureResultReadReceiverFunc mResultFunc = nullptr;

    virtual void on_read(TResult &result);

    virtual bool onConvert(std::string &srcLine, TValue &convertedValue) = 0;
};

template<class TValue, class TData, class TResult>
template<class TViewModel>
void BaseReader<TValue, TData, TResult>::bind_result(BaseReader::ResultReadReceiverFunc<TViewModel> func) {
    mResultFunc = static_cast<_PureResultReadReceiverFunc>(func);
}

template<class TValue, class TData, class TResult>
bool BaseReader<TValue, TData, TResult>::fire_result(IViewModel &ctrl, TResult &result) {
    if (mResultFunc)
        return (ctrl.*mResultFunc)(result);
    return true;
}

template<class TValue, class TData, class TResult>
void BaseReader<TValue, TData, TResult>::run(IViewModel &ctrl) {
    if (!static_cast<IElementData&>(_BaseCuiElement::data()).visible())
        return;

    this->onBeforeRun();

    _BaseCuiElement::fire_data(ctrl);

    OutputHelper outHelp;
    outHelp.beginColorize(std::cout);
    while (true) {
        outHelp.saveState();
        outHelp.applyColor(
            static_cast<BaseReaderData &>(_BaseCuiElement::data()).read_color());

        TResult result;
        on_read(result);

        outHelp.resetColors();
        if (fire_result(ctrl, result))
            break;
        outHelp.backState();
    }
    outHelp.endColorize();

    this->onAfterRun();
}

template<class TValue, class TData, class TResult>
void BaseReader<TValue, TData, TResult>::on_read(TResult &result) {
    auto &castedResult = static_cast<ReaderResult<TValue> &>(result);
    auto &castedData = static_cast<ReaderData<TValue> &>(_BaseCuiElement::data());

    std::string lineValue;
    std::getline(std::cin, lineValue);
    text::trim(lineValue);

    if (lineValue.empty()) {
        castedResult.assign_empty();
    } else {
        bool isCommand = (lineValue[0] == '\\');
        if (isCommand || lineValue[0] == '@')
            lineValue.erase(0, 1);

        if (isCommand) {
            castedResult.assign_command(lineValue);
        } else {
            TValue convertedValue;
            if (onConvert(lineValue, convertedValue)) {
                auto errorList = castedData.validate(convertedValue);
                if (errorList.empty())
                    castedResult.assign_value(convertedValue);
                else
                    castedResult.assign_invalid(errorList);
            } else {
                castedResult.assign_convert_fail(castedData.convert_fail_text());
            }
        }
    }
}

}




