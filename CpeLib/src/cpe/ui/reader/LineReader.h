#pragma once

#include <string>

#include "ReaderBase.h"
#include "IConverter.h"

namespace cpe {

class LineReader : public ReaderBase<std::string> {
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



