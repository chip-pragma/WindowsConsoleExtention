#include "BaseInput.h"
#include "cpe/core/Platform.h"

namespace cpe::ui {

using namespace cpe::core;

BaseInput::BaseInput() = default {
    _readFinished = false;
}

void BaseInput::read() {
    for (; !_readFinished;) {
        KeyType keyType;
        char sym;
        if (!platform::getKey(keyType, sym))
            onReadingError();
        if (keyType == KeyType::Symbol
            && _inFormat.preprocess(sym))
            onReceiveSymbol(sym);
        else
            onReceiveCommand(keyType);
    }
    _readFinished = false;
}

void BaseInput::finishRead() {
    _readFinished = true;
}

const InputFormat &BaseInput::getInputFormat() const {
    return _inFormat;
}

void BaseInput::setInputFormat(const InputFormat &inFormat) {
    _inFormat = inFormat;
}


}