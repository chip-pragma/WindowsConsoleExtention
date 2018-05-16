#pragma once

#include <string>

#include "Reader.h"
#include "IConverter.h"

namespace cpe {

class LineReader : public Reader<std::string> {
public:
    LineReader();

private:
    class _LineConverter : public IConverter<std::string> {
    public:
        bool convert(const std::string &lineValue, std::string &outValue, std::string &errorText) const override;
    };

    _LineConverter mConverter;
};

}



