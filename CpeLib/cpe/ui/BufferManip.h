#pragma once

#include "Buffer.h"
#include "cpe/core/Color.h"

namespace cpe {

Buffer &bg(Buffer &buf);

Buffer &fg(Buffer &buf);

Buffer &operator<<(Buffer &buf, const Color &color);

Buffer &unset(Buffer &buf);

Buffer &flush(Buffer &buf);

}