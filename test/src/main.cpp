#include <iostream>
#include <utility>
#include <cpe/core/terminal.h>
#include <cpe/ui/write/TextCanvas.h>
#include <cpe/ui/element/reader/IValidator.h>
#include <cpe/ui/element/reader/IConverter.h>
#include <cpe/ui/element/reader/Reader.h>
#include <cpe/ui/element/MessageBox.h>

#include "common.h"

using namespace cpe;

class Int32Converter : public IConverter<int32_t> {
public:
    bool convert(const std::string &lineValue, int32_t &outValue, std::string &errorText) const override {
        try {
            outValue = std::stoi(lineValue);
        } catch (std::logic_error &except) {
            errorText = "Введите целое число"_dos;
            return false;
        }
        return true;
    }
};

class Int32Validator : public IValidator<int32_t> {
public:
    void validate(const int32_t &value, ReaderErrorVector &outErrors) const override {
        if ((value < 0 || value > 9) && value != 13)
            outErrors.push_back("Число должно быть в диапазоне [0; 9] или равным 13"_dos);
    }
};

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();



    MessageBox mb;
    mb.border_style(DualBorder::NONE);
    mb.show();
    mb.border_style(DualBorder::LEFT);
    mb.show();
    mb.border_style(DualBorder::RIGHT);
    mb.show();
    mb.border_style(DualBorder::TOP);
    mb.show();
    mb.border_style(DualBorder::BOTTOM);
    mb.show();

    mb.border_style(DualBorder::OUT_ALL);
    mb.show();
    mb.border_style(DualBorder::IN_ALL);
    mb.show();

    mb.border_style(DualBorder::IN_V);
    mb.show();
    mb.border_style(DualBorder::IN_H);
    mb.show();

    mb.border_style(DualBorder::OUT_V);
    mb.show();
    mb.border_style(DualBorder::OUT_H);
    mb.show();


    term::pause();

    return 0;
}
