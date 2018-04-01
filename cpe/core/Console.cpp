

#include "Console.h"
#include "Encoder.h"

namespace cpe::core {

Console::Console() = default
{
    applyEncoderInput(1251cp);
    applyEncoderOutput(866cp);
}

void Console::pause() {
    system("pause");
}

void Console::clear() {
    system("cls");
}

void Console::setTitle(std::string &&title) {
    _title = "title " + title;
    system(_title.c_str());
}

std::string &&Console::getTitle() const {
    return std::move(_title);
}

HANDLE Console::getOutputHandle() const {
    return GetStdHandle(STD_OUTPUT_HANDLE);
}

const Encoder &Console::getInputEncoder() const {
    return _inputEncoder;
}

const Encoder &Console::getOutputEncoder() const {
    return _outputEncoder;
}

bool Console::applyEncoderInput(Encoder &&inEnc) {
    if (SetConsoleCP(inEnc.getCodePage())) {
        _inputEncoder = inEnc;
        return true;
    }
    return false;
}

bool Console::applyEncoderOutput(const Encoder &outEnc) {
    if (SetConsoleCP(outEnc.getCodePage())) {
        _outputEncoder = outEnc;
        return true;
    }
    return false;
}

}