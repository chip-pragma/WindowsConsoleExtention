#include "BufferManip.h"

namespace cpe {

Buffer &bg(Buffer &buf) {
    buf.setColorSetBg(true);
    return buf;
}

Buffer &fg(Buffer &buf) {
    buf.setColorSetBg(false);
    return buf;
}

Buffer &operator<<(Buffer &buf, const Color &color) {
    buf.setColor(color);
    return buf;
}

Buffer &unset(Buffer &buf) {
    buf.unsetColor();
    return buf;
}

Buffer &flush(Buffer &buf) {
    buf.flush();
    return buf;
}

}