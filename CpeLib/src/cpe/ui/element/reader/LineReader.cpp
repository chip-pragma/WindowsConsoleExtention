#include "LineReader.h"
#include "cpe/tool/text.h"


namespace cpe {

bool LineReader::read(std::string &outValue) {
    std::string valueRead;

    output_begin(std::cout);

    static const int RESULT_NONE = 0;
    static const int RESULT_NOT_REQUIRED= 1;
    static const int RESULT_SUCCESSFUL = 2;

    int result = RESULT_NONE;
    while (result == RESULT_NONE) {
        state_save();
        output_apply_style(mReadStyle);
        std::getline(std::cin, valueRead);

        if (valueRead.empty() && !mRequired) {
            result = RESULT_NOT_REQUIRED;
        } else if (!valueRead.empty()) {
            std::vector<std::string> errors;
            validate(valueRead, errors);

            if (!errors.empty() && mSkipError) {
                break;
            } else if (!errors.empty()) {
                output_apply_style(mErrorStyle);
                for (const auto& err : errors)
                    std::cout << "[X] " << err << "\n";
                std::cout.flush();
                output_reset_style();
                term::pause();
            } else {
                outValue = valueRead;
                result = RESULT_SUCCESSFUL;
            }
        }

        output_reset_style();
        state_clear_back();
    }

    output_end();
    return (result == RESULT_SUCCESSFUL);
}

}



