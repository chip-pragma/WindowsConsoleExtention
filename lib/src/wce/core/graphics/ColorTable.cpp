#include "ColorTable.h"

namespace wce {

void ColorTable::setColor(ColorIndex index, Color color) {
    m_colors[index.get()] = color;
}

Color ColorTable::getColor(ColorIndex index) const {
    return m_colors[index.get()];
}

}