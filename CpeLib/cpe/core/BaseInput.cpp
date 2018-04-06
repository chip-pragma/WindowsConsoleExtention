#include "BaseInput.h"
#include "cpe/core/Platform.h"

namespace cpe::core {

BaseInput::BaseInput() {
    _readFinished = false;
    _inFormat = nullptr;
}

void BaseInput::startRead() {
    for (; !_readFinished;) {
        KeyType keyType;
        char sym;
        uint32_t ec = platform::getKey(keyType, sym);
        if (ec != 0) {
            onReadingError(ec);
            _readFinished = true;
        } else if (keyType == KeyType::Symbol
            && (_inFormat == nullptr
                || _inFormat->preprocess(sym))) {
            onReceiveSymbol(sym);
        } else {
            onReceiveCommand(keyType);
        }
    }
    _readFinished = false;
}

void BaseInput::finishRead() {
    _readFinished = true;
}

const InputFormat &BaseInput::getInputFormat() const {
    return *_inFormat;
}

void BaseInput::setInputFormat(const InputFormat &inFormat) {
    _inFormat = &inFormat;
}

void BaseInput::cleanInputFormat() {
    _inFormat = nullptr;
}


}