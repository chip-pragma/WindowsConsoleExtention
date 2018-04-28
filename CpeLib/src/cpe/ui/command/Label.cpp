#include "Label.h"
#include "cpe/utils/Encoder.h"

#include "cpe/ui/BufferManip.h"

namespace cpe {

Label::Label() {
    propAssign(text, &Label::textSetter);
}

Label::~Label() {

}

void *Label::run(Buffer &buf, std::vector<AReader *> &readers) {
    buf << setBack << back()
        << setFore << fore()
        << text();
}

void Label::textSetter(const std::string &value) {
    Encoder<Encoding::UTF8> encUtf8;
    Encoder<Encoding::CP866> encCp866;

    if (value == encCp866.to(encUtf8.from("It's changed 3!"))) {
        back(Colors::RED);
        fore(Colors::LT_YELLOW);
        text("Gotcha!");
    }

    propValue(text, value);
}

}
