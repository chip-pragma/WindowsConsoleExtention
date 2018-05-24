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
    using ResultReadReceiverFunc = void (TViewModel::*)(TResult &);

    virtual ~BaseReader() { }

    template<class TViewModel>
    void bind_result(ResultReadReceiverFunc<TViewModel> func);

    void fire_result(IViewModel &ctrl, TResult &result);

    void run(IViewModel &ctrl) override;

protected:
    using _PureResultReadReceiverFunc  = void (IViewModel::*)(TResult &);

    _PureResultReadReceiverFunc mResultFunc = nullptr;

    virtual void on_read(TResult &result);

    virtual bool on_convert(std::string &srcLine, TValue &convertedValue) = 0;
};

template<class TValue, class TData, class TResult>
template<class TViewModel>
void BaseReader<TValue, TData, TResult>::bind_result(BaseReader::ResultReadReceiverFunc<TViewModel> func) {
    mResultFunc = static_cast<_PureResultReadReceiverFunc>(func);
}

template<class TValue, class TData, class TResult>
void BaseReader<TValue, TData, TResult>::fire_result(IViewModel &ctrl, TResult &result) {
    if (mResultFunc)
        (ctrl.*mResultFunc)(result);
}

template<class TValue, class TData, class TResult>
void BaseReader<TValue, TData, TResult>::run(IViewModel &ctrl) {
    if (!static_cast<IElementData&>(_BaseCuiElement::data()).visible())
        return;

    _BaseCuiElement::fire_data(ctrl);

    OutputHelper outHelp;
    outHelp.begin_colorized(std::cout);
    while (true) {
        outHelp.save_state();
        outHelp.apply_color(
                static_cast<BaseReaderData &>(_BaseCuiElement::data()).read_color());

        TResult result;
        on_read(result);

        outHelp.reset_colors();
        fire_result(ctrl, result);
        if (static_cast<ReaderResult<TValue>>(result).is_read_applied())
            break;
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




