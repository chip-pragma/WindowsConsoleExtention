#include "Label.h"

namespace wce {

Label::~Label() { }

void Label::onWrite(Buffer &buf) {
    buf.draw(text);
}

}