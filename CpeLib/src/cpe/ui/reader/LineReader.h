#pragma once

#include <string>

#include "ReaderBaseTemplate.h"
#include "ReaderBase.h"
#include "IConverter.h"

namespace cpe {

class LineReader : public ReaderBaseTemplate<std::string, ReaderInitializer, ResultRead<std::string>> {
public:
    LineReader();

protected:

    ReaderInitializer make_initializer() override;

private:
    class _LineConverter : public IConverter<std::string> {
    public:
        bool convert(const std::string &lineValue, std::string &outValue, std::string &errorText) const override;
    };

    _LineConverter mConverter;
};

}



