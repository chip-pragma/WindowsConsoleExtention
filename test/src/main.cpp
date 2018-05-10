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

#undef MessageBox

inline void show_message(MessageBox& mb, const DualBorder& db) {
    mb.border_style(db);
    mb.show();
}

int main() {
    term::title("Текст консоли"_dos);
    term::foreground(Colors::WHITE);
    term::background(Colors::BLACK);

    term::pause();

    MessageBox mb;
    std::cout << "NONE:\n";
    show_message(mb, DualBorder::NONE);
    std::cout << "LEFT:\n";
    show_message(mb, DualBorder::LEFT);
    std::cout << "RIGHT:\n";
    show_message(mb, DualBorder::RIGHT);
    std::cout << "TOP:\n";
    show_message(mb, DualBorder::TOP);
    std::cout << "BOTTOM:\n";
    show_message(mb, DualBorder::BOTTOM);
    std::cout << "OUT_ALL:\n";
    show_message(mb, DualBorder::OUT_ALL);
    std::cout << "IN_ALL:\n";
    show_message(mb, DualBorder::IN_ALL);
    std::cout << "IN_V:\n";
    show_message(mb, DualBorder::IN_V);
    std::cout << "IN_H:\n";
    show_message(mb, DualBorder::IN_H);
    std::cout << "OUT_V:\n";
    show_message(mb, DualBorder::OUT_V);
    std::cout << "OUT_H:\n";
    show_message(mb, DualBorder::OUT_H);

    std::cout << "LEFT | TOP | IN_V:\n";
    show_message(mb, DualBorder::RIGHT | DualBorder::TOP | DualBorder::IN_V);
    std::cout << "LEFT | TOP | IN_H:\n";
    show_message(mb, DualBorder::LEFT | DualBorder::BOTTOM | DualBorder::IN_H);


    term::pause();

    return 0;
}
