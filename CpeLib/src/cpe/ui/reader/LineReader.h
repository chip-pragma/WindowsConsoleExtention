#pragma once

#include <string>

#include "BaseReader.h"
#include "IConverter.h"

namespace cpe {

class LineReader : public BaseReader<ReaderData<std::string>, std::string, ResultRead<std::string>> {
public:
    explicit LineReader(const IConverter<ReaderData<std::string>> &converter);

protected:
    class _LineConverter : public IConverter<std::string> {
    public:
        bool convert(const std::string &lineValue, std::string &outValue, std::string &errorText) const override;
    };

    _LineConverter mConverter;
};

}



