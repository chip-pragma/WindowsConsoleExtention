#include <cpe/ui/style/TextColor.h>
#include "ReaderStyleBase.h"

namespace cpe {

ReaderInitializer::ReaderInitializer(ReaderStyleBase &element)
        : IInitializer(static_cast<ICuiElement &>(element)),
          mReader(element) {
}

TextColor &ReaderInitializer::read_color() {
    return mReader.read_color();
}

const TextColor &ReaderStyleBase::read_color() const {
    return mReadStyle;
}

TextColor &ReaderStyleBase::read_color() {
    return mReadStyle;
}

}



