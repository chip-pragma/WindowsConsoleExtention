#include "DualBorder.h"

namespace cpe {

bool operator==(const DualBorder &db, uint8_t i) {
    return db == static_cast<DualBorder>(i);
}

bool operator!=(const DualBorder &db, uint8_t i) {
    return !(db == i);
}

DualBorder operator&(const DualBorder &db1, const DualBorder &db2) {
    return static_cast<DualBorder>(
            static_cast<uint8_t>(db1) & static_cast<uint8_t>(db2));
}

DualBorder operator|(const DualBorder &db1, const DualBorder &db2) {
    return static_cast<DualBorder>(
            static_cast<uint8_t>(db1) | static_cast<uint8_t>(db2));
}

}