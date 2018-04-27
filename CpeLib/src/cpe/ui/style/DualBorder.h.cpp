#include "DualBorder.h"

namespace cpe {

DualBorder operator&(const DualBorder &db1, const DualBorder &db2) {
    return (DualBorder) ((unsigned char) db1 & (unsigned char) db2);
}

DualBorder operator|(const DualBorder &db1, const DualBorder &db2) {
    return (DualBorder) ((unsigned char) db1 | (unsigned char) db2);
}

}