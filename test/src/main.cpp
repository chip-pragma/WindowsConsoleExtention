#include <iostream>

#include <cpe/core/terminal.h>
#include <cpe/ui/write/TextCanvas.h>
#include <cpe/ui/element/reader/LineReader.h>
#include <cpe/ui/element/reader/IValidator.h>

#include "common.h"

using namespace cpe;

class LengthValidator : public IValidator<std::string> {
public:
    void operator()(const std::string &value, ValidateErrorList &outErrors) const override {
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

    cpe::LineReader reader;
    reader.mod_read_style().mod_foreground().set(cpe::Colors::LT_GREEN);
    reader.mod_read_style().mod_background().set(cpe::Colors::BLUE);
    reader.mod_error_style().mod_foreground().set(cpe::Colors::BLACK);
    reader.mod_error_style().mod_background().set(cpe::Colors::WHITE);
    LengthValidator valid;
    reader.add_validator(valid);

    std::string value = "Старуха"_dos;
    if (reader.read(value))
        std::cout << "Введено: "_dos << value << std::endl;
    else
        std::cout << "Не считано: "_dos << value << std::endl;

    term::pause();

    return 0;
}
