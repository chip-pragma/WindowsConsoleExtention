#include "common.h"

namespace {

wce::Encoder encUtf8(wce::Encoder::UTF8);
wce::Encoder encCp866(wce::Encoder::CP866);

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
