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
    template<class TController>
    using ResultReadReceiverFunc = void (TController::*)(TResult &);

    virtual ~BaseReader() { }

    template<class TController>
    void bind_result(ResultReadReceiverFunc<TController> func);

    void fire_result(IController &ctrl, TResult &result);

    void run(IController &ctrl) override;

protected:
    using _PureResultReadReceiverFunc  = void (IController::*)(TResult &);

    _PureResultReadReceiverFunc mResultFunc = nullptr;

    virtual void on_read(TResult &result);

    virtual bool on_convert(std::string &srcLine, TValue &convertedValue) = 0;
};

template<class TValue, class TData, class TResult>
template<class TController>
void BaseReader<TValue, TData, TResult>::bind_result(BaseReader::ResultReadReceiverFunc<TController> func) {
    mResultFunc = static_cast<_PureResultReadReceiverFunc>(func);
}

template<class TValue, class TData, class TResult>
void BaseReader<TValue, TData, TResult>::fire_result(IController &ctrl, TResult &result) {
    if (mResultFunc)
        (ctrl.*mResultFunc)(result);
}

template<class TValue, class TData, class TResult>
void BaseReader<TValue, TData, TResult>::run(IController &ctrl) {
    _BaseCuiElement::fire_data(ctrl);

    OutputHelper outHelp;
    outHelp.begin_colorized(std::cout);
    while (true) {
        outHelp.save_state();
        outHelp.apply_color(
                static_cast<BaseReaderData &>(_BaseCuiElement::data()).read_color());

        TResult result;
        on_read(result);
        fire_result(ctrl, result);
        if (static_cast<ReaderResult<TValue>>(result).is_read_applied())
            break;

        outHelp.reset_colors();
        outHelp.back_state();
    }
    outHelp.end_colorized();
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
            if (on_convert(lineValue, convertedValue)) {
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




