#include "common.h"

namespace {

cpe::Encoder<cpe::Encoding::UTF8> encUtf8;
cpe::Encoder<cpe::Encoding::CP866> encCp866;

}

/**
 * Кодирует строку из UTF8 в CP866
 */
std::string operator "" _dos(const char *src, size_t size) {
    return encCp866.to(encUtf8.from(src));
}