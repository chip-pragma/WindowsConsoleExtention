#pragma once

#include <iostream>

#include "cpe/core/terminal.h"
#include "cpe/core/Point.h"
#include "cpe/core/Color.h"
#include "cpe/ui/property/PropertyAbstract.h"

namespace cpe {

template<class TValue>
class ReaderAbstract {
public:
    explicit ReaderAbstract(PropertyWriteInterface <TValue> &readInto);

    explicit ReaderAbstract(PropertyWriteInterface <TValue> &readInto, const std::string &hint);

    const std::string &hint() const;

    void hint(const std::string &hint);

protected:
    std::string mHint;

    void startRead();

    void finishRead(const TValue& valueRead, bool clearBefore);

private:
    struct {
        Color prevBack;
        Color prevFore;
        Point prevCursor;
    } _mOutputBufferRead;

    PropertyWriteInterface<TValue> *_mPropInto;
};

template<class TValue>
ReaderAbstract<TValue>::ReaderAbstract(PropertyWriteInterface <TValue> &readInto) {
    _mPropInto = &readInto;
}

template<class TValue>
ReaderAbstract<TValue>::ReaderAbstract(PropertyWriteInterface <TValue> &readInto, const std::string &hint) {
    _mPropInto = &readInto;
    mHint = hint;
}

template<class TValue>
const std::string &ReaderAbstract<TValue>::hint() const {
    return mHint;
}

template<class TValue>
void ReaderAbstract<TValue>::hint(const std::string &hint) {
    mHint = hint;
}

template<class TValue>
void ReaderAbstract<TValue>::startRead() {
    _mOutputBufferRead.prevBack = term::background();
    _mOutputBufferRead.prevFore = term::foreground();
    _mOutputBufferRead.prevCursor = term::cursorPosition();

    term::background(Colors::BLUE);
    term::foreground(Colors::LT_TEAL);
    std::cout << "[" << hint() << "]\n> ";
    term::foreground(Colors::WHITE);
}

template<class TValue>
void ReaderAbstract<TValue>::finishRead(const TValue &valueRead, bool clearBefore) {
    (*_mPropInto)(valueRead);

    term::background(_mOutputBufferRead.prevBack);
    term::foreground(_mOutputBufferRead.prevFore);

    if (clearBefore) {
        // TODO очистка текста ввода
    }
}

}




