#include "common.h"

namespace {

cpe::Encoder encUtf8(cpe::Encoder::UTF8);
cpe::Encoder encCp866(cpe::Encoder::CP866);

}

/**
 * Кодирует строку из UTF8 в CP866
 */
std::string operator "" _dos(const char *src, size_t size) {
    return encCp866.to(encUtf8.from(src));
}

std::string fromUtf8ToDos866(const std::string &src) {
    return encCp866.to(encUtf8.from(src));
}
