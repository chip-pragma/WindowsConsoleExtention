#pragma once

#include "Buffer.h"
#include "cpe/core/Color.h"

namespace cpe {

Buffer &backColorMode(Buffer &buf);

Buffer &foreColorMode(Buffer &buf);

Buffer &operator<<(Buffer &buf, const Color &color);

Buffer &clearColor(Buffer &buf);

Buffer &flush(Buffer &buf);

}