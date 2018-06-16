#include "ColorIndex.h"

#include "Exception.h"

namespace wce {

ColorIndex::ColorIndex(uint8_t index) : m_index(index) {
    if (index < 0 || index > 15)
        throw Exception("Index must be into [0; 15]");
}

uint8_t ColorIndex::get() const {
    return m_index;
}

bool ColorIndex::operator==(const ColorIndex &rhs) const {
    return m_index == rhs.m_index;
}

bool ColorIndex::operator!=(const ColorIndex &rhs) const {
    return !(rhs == *this);
}

}