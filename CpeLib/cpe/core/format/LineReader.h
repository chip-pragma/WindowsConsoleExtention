#pragma once

#include <string>

#include <cpe/core/BaseInput.h>
#include <cpe/core/BaseOutput.h>

namespace cpe::core::format {

class LineReader :
        public BaseInput,
        protected BaseOutput {
public:
    LineReader();

    void read(std::string &line, const OutputFormat &format);

protected:
    void onReceiveSymbol(const char &symbol) override;

    void onReceiveCommand(const KeyType &command) override;

    void onReadingError(uint32_t errCode) override;



private:
    std::string *_line;

    void output() override;
};

}




