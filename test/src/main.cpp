#include <iostream>
#include <utility>
#include <cpe/core/terminal.h>
#include <cpe/ui/write/TextCanvas.h>
#include <cpe/ui/element/reader/IValidator.h>
#include <cpe/ui/element/reader/ConverterBase.h>
#include <cpe/ui/element/reader/Reader.h>

#include "common.h"

using namespace cpe;

class LineConverter : public ConverterBase<std::string> {
public:
    explicit LineConverter() : ConverterBase("") {}

    bool operator()(const std::string &lineValue, std::string &outValue) const override {
        outValue = lineValue;
        return true;
    }
};

class LengthValidator : public IValidator<std::string> {
public:
    void operator()(const std::string &value, ReaderErrorVector &outErrors) const override {
        if (value.length() > 5)
            outErrors.push_back("Длина текста больше 5 символов!"_dos);
        if (value.find("Ъ"_dos) != std::string::npos)
            outErrors.push_back("Строка содержит странный символ 'Ъ'!"_dos);
    }
};

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

    LineConverter lc;
    Reader<std::string> reader(lc);
    reader.mod_read_style().mod_foreground().set(Colors::LT_GREEN);
    reader.mod_read_style().mod_background().set(Colors::BLUE);
    reader.mod_error_style().mod_foreground().set(Colors::BLACK);
    reader.mod_error_style().mod_background().set(Colors::WHITE);
    LengthValidator valid;
    reader.add_validator(valid);

    std::string value = "Старуха"_dos;
    reader.read(value);
    std::cout << "Введено: "_dos << value << std::endl;

    term::pause();

    return 0;
}
