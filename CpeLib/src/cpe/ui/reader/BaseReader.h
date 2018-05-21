#pragma once

#include <iostream>
#include <vector>

#include "cpe/tool/text.h"
#include "cpe/ui/output/OutputHelper.h"
#include "ReaderData.h"
#include "cpe/ui/BaseCuiElement.h"
#include "IReader.h"
#include "IConverter.h"
#include "IValidator.h"
#include "ResultRead.h"

namespace cpe {

template<class TData, class TValue, class TResult>
class BaseReader : public BaseCuiElement<TData>,
                   public IReader<TResult> {

    using _BaseCuiElement = BaseCuiElement<TData>;
public:
    template<class TController>
    using ResultReadReceiverFunc = void (TController::*)(TResult &);

    explicit BaseReader(const IConverter<TValue> &converter);

    virtual ~BaseReader() { }

    virtual void read(TResult &result);

    template<class TController>
    void bind_result(ResultReadReceiverFunc<TController> func);

    void fire_result(IController &ctrl, TResult &result);

    void run(IController &ctrl) override;

protected:
    using _PureResultReadReceiverFunc  = void (IController::*)(TResult &);

    _PureResultReadReceiverFunc mResultFunc = nullptr;
    const IConverter<TValue>* mConverter;

    virtual void on_read(TResult &result);
};

template<class TData, class TValue, class TResult>
BaseReader<TData, TValue, TResult>::BaseReader(const IConverter<TValue> &converter)
        : mConverter(&converter) { };

template<class TData, class TValue, class TResult>
void BaseReader<TData, TValue, TResult>::read(TResult &result) {
    on_read(result);
}

template<class TData, class TValue, class TResult>
template<class TController>
void BaseReader<TData, TValue, TResult>::bind_result(BaseReader::ResultReadReceiverFunc<TController> func) {
    mResultFunc = static_cast<_PureResultReadReceiverFunc>(func);
}

template<class TData, class TValue, class TResult>
void BaseReader<TData, TValue, TResult>::fire_result(IController &ctrl, TResult &result) {
    if (mResultFunc)
        (ctrl.*mResultFunc)(result);
}

template<class TData, class TValue, class TResult>
void BaseReader<TData, TValue, TResult>::run(IController &ctrl) {
    _BaseCuiElement::fire_data(ctrl);

    OutputHelper outHelp;
    outHelp.begin_colorized(std::cout);
    while (true) {
        outHelp.save_state();
        outHelp.apply_color(
                static_cast<BaseReaderData&>(_BaseCuiElement::data()).read_color());

        TResult result;
        read(result);
        fire_result(ctrl, result);
        if (static_cast<ResultRead<TValue>>(result).is_read_applied())
            break;

        outHelp.reset_colors();
        outHelp.back_state();
    }
    outHelp.end_colorized();
}

template<class TData, class TValue, class TResult>
void BaseReader<TData, TValue, TResult>::on_read(TResult &result) {
    auto &castedResult = static_cast<ResultRead<TValue> &>(result);

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
            std::string oneError;
            if (mConverter.convert(lineValue, convertedValue, oneError)) {
                std::vector<std::string> errorList;
                for (const IValidator<TValue> &validator :
                        static_cast<ReaderData<TValue>>(_BaseCuiElement::data()).validators()) {
                    validator.validate(convertedValue, errorList);
                }

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

}




