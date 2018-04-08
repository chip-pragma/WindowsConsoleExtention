#pragma once

#include <string>

#include <cpe/core/BaseInput.h>
#include <cpe/core/BaseOutput.h>

namespace cpe::core::format {

class LineReader :
        public BaseInput {
public:
    LineReader();

    void read(std::string &line, const OutputFormat &format);

protected:
    void onKeyRead(const char &symbol) override;

    void onReadingError(uint32_t errCode) override;



private:
    std::string *_line;
    OutputFormat _outFormat;
};

}




