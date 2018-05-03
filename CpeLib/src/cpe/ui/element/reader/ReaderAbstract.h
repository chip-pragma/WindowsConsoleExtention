#pragma once

#include <iostream>

#include "cpe/core/terminal.h"
#include "cpe/core/Point.h"
#include "cpe/core/Color.h"
#include "cpe/utils/text.h"
#include "cpe/ui/ObserverInterface.h"
#include "cpe/ui/ProviderInterface.h"

namespace cpe {

template<class TValue>
class ReaderAbstract {
public:
    template <class TObserver>
    using ValueReadFunc = void (TObserver::*)(const TValue &);
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
    using PureValueReadFunc = void (ObserverInterface::*)(const TValue &);
    using PureHintParamFunc = std::string (ProviderInterface::*)() const;

    std::string mHint;

    void startRead(const ProviderInterface &provider);

    void finishRead(ObserverInterface &observer, const TValue &valueRead, bool clearBefore);

private:
    PureValueReadFunc _mValueReadFunc = nullptr;
    PureHintParamFunc _mHintParamFunc = nullptr;

    struct {
        Color prevBack;
        Color prevFore;
        Point prevCursor;
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
void ReaderAbstract<TValue>::startRead(const ProviderInterface &provider) {
    _mOutputBufferRead.prevBack = term::background();
    _mOutputBufferRead.prevFore = term::foreground();
    _mOutputBufferRead.prevCursor = term::cursorPosition();

    auto hintFull = mHint;
    if (_mHintParamFunc) {
        auto hintParam = (provider.*_mHintParamFunc)();
        text::replace(hintFull, HINT_PARAM_TEMPLATE, hintParam);
    }

    term::background(Colors::BLUE);
    term::foreground(Colors::LT_TEAL);
    std::cout << "[" << hintFull << "]\n> ";
    term::foreground(Colors::WHITE);
}

template<class TValue>
void ReaderAbstract<TValue>::finishRead(ObserverInterface &observer, const TValue &valueRead, bool clearBefore) {
    if (_mValueReadFunc)
        (observer.*_mValueReadFunc)(valueRead);

    term::background(_mOutputBufferRead.prevBack);
    term::foreground(_mOutputBufferRead.prevFore);

    if (clearBefore) {
        // TODO очистка текста ввода
        // TODO переработка Buffer
    }
}

}




