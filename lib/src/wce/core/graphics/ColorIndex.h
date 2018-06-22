#pragma once

#include <cstdint>

namespace wce {

class ColorIndex {
public:
    ColorIndex(uint8_t index); // NOLINT

    uint8_t get() const;

    bool operator==(const ColorIndex &rhs) const;

    bool operator!=(const ColorIndex &rhs) const;

private:
    uint8_t m_index;
};

}




