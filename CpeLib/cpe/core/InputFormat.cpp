#include "InputFormat.h"

namespace cpe::core {


InputFormat::InputFormat() {
    _allowedChars = "";
}

bool InputFormat::preprocess(char &c) const {
    auto allowed = checkAllowChar(c);

    return allowed;
}

const std::string &InputFormat::getAllowedChars() const {
    return _allowedChars;
}

void InputFormat::setAllowedChars(const std::string &allowedChars) {
    _allowedChars = allowedChars;
}

bool InputFormat::checkAllowChar(const char &c) const {
    return !_allowedChars.empty()
           && _allowedChars.find(c) != std::string::npos;
}


}