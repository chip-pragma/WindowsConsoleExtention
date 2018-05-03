#pragma once

#include <iostream>

#include "cpe/core/terminal.h"
#include "cpe/core/Point.h"
#include "cpe/core/Color.h"
#include "cpe/utils/text.h"
#include "cpe/ui/ObserverInterface.h"
#include "cpe/ui/ProviderInterface.h"
#include "cpe/ui/WriterAbstract.h"

namespace cpe {

template<class TValue>
class ReaderAbstract : public WriterAbstract {
public:
    template <class TObserver>
    using ValueReadFunc = bool (TObserver::*)(const TValue &);
    template <class TProvider>
    using HintParamFunc = std::string (TProvider::*)() const;

    constexpr static const char * HINT_PARAM_TEMPLATE = "%{hint}";

    template <class TObserver>
    void assignObserver(ValueReadFunc<TObserver> func);

    void rejectValueReadObserver();

    template <class TProvider>
    void assignProvider(HintParamFunc<TProvider> func);

    void rejectHintParamProvider();

    const std::string &hint() const;

    void hint(const std::string &text);

protected:
    using PureValueReadFunc = bool (ObserverInterface::*)(const TValue &);
    using PureHintParamFunc = std::string (ProviderInterface::*)() const;

    std::string mHint;

    std::string getHint(const ProviderInterface &provider);

    virtual bool validateRead(ObserverInterface &observer, const TValue &value);

private:
    PureValueReadFunc _mValueReadFunc = nullptr;
    PureHintParamFunc _mHintParamFunc = nullptr;

    struct {
        Color prevBack;
        Color prevFore;
    } _mOutputBufferRead;

};

template<class TValue>
template<class TObserver>
void ReaderAbstract<TValue>::assignObserver(ReaderAbstract::ValueReadFunc<TObserver> func) {
    _mValueReadFunc = static_cast<PureValueReadFunc>(func);
}

template<class TValue>
void ReaderAbstract<TValue>::rejectValueReadObserver() {
    _mValueReadFunc = nullptr;
}

template<class TValue>
template<class TProvider>
void ReaderAbstract<TValue>::assignProvider(ReaderAbstract::HintParamFunc<TProvider> func) {
    _mHintParamFunc = static_cast<PureHintParamFunc>(func);
}

template<class TValue>
void ReaderAbstract<TValue>::rejectHintParamProvider() {
    _mHintParamFunc = nullptr;
}

template<class TValue>
const std::string &ReaderAbstract<TValue>::hint() const {
    return mHint;
}

template<class TValue>
void ReaderAbstract<TValue>::hint(const std::string &text) {
    mHint = text;
}

template<class TValue>
std::string ReaderAbstract<TValue>::getHint(const ProviderInterface &provider) {
    auto hintFull = mHint;
    if (_mHintParamFunc) {
        auto hintParam = (provider.*_mHintParamFunc)();
        text::replace(hintFull, HINT_PARAM_TEMPLATE, hintParam);
    }
    return hintFull;
}

template<class TValue>
bool ReaderAbstract<TValue>::validateRead(ObserverInterface &observer, const TValue &value) {
    if (_mValueReadFunc)
        return (observer.*_mValueReadFunc)(value);
    return true;
}

}




