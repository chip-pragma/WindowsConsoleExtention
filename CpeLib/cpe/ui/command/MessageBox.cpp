#include "MessageBox.h"

namespace cpe {

MessageBox::MessageBox() {
    propCreate(caption.text);
    propCreate(caption.icon, '!');
    propCreate(caption.back);
    propCreate(caption.fore);
    propCreate(message.text);
    propCreate(message.fore);
    propCreate(message.back);
    propCreate(message.menu);
    propCreate(border.fore);
    propCreate(border.back);
    propCreate(border.dual);
}

MessageBox::~MessageBox() {
    propDestroyAll();
}

void *MessageBox::run(Buffer &buf, std::vector<AReader *> &readers) {

}


}


