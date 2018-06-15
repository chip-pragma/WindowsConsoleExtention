#include "ISerializable.h"

namespace wce {
std::ostream &operator<<(std::ostream &os, const ISerializable &sObj) {
    sObj.onSerialize(os);
    return os;
}

std::istream &operator>>(std::istream &is, const ISerializable &desObj) {
    desObj.onDeserialize(is);
    return is;
}
}