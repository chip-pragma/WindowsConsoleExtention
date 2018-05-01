#include "BufferManip.h"

namespace cpe {

Buffer &backColorMode(Buffer &buf) {
    buf.colorMode(true);
    return buf;
}

Buffer &foreColorMode(Buffer &buf) {
    buf.colorMode(false);
    return buf;
}

Buffer &operator<<(Buffer &buf, const Color &color) {
    buf.color(color);
    return buf;
}

Buffer &clearColor(Buffer &buf) {
    buf.clearColor();
    return buf;
}

Buffer &flush(Buffer &buf) {
    buf.flush();
    return buf;
}

}