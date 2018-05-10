#include "DualBorder.h"

namespace cpe {

bool operator==(const DualBorder &db, int32_t i) {
    return db == static_cast<DualBorder>(i);
}

bool operator!=(const DualBorder &db, int32_t i) {
    return !(db == i);
}

DualBorder operator&(const DualBorder &db1, const DualBorder &db2) {
    return (DualBorder) ((unsigned char) db1 & (unsigned char) db2);
}

DualBorder operator|(const DualBorder &db1, const DualBorder &db2) {
    return (DualBorder) ((unsigned char) db1 | (unsigned char) db2);
}

}