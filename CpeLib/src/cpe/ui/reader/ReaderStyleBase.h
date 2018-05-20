#pragma once

#include <string>
#include <set>

#include "IReader.h"
#include "cpe/ui/IInitializer.h"
#include "cpe/ui/style/TextColor.h"

namespace cpe {

class ReaderStyleBase;

class ReaderInitializer : public IInitializer {
public:
    explicit ReaderInitializer(ReaderStyleBase &element);

    TextColor &read_color();

protected:
    ReaderStyleBase &mReader;
};

class ReaderStyleBase : public IReader {
public:
    const TextColor &read_color() const;

    TextColor &read_color();

protected:
    TextColor mReadStyle;
};

}




