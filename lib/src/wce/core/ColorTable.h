#pragma once

#include "Color.h"
#include "ColorIndex.h"

namespace wce {

class ColorTable {
public:
    void setColor(ColorIndex index, Color color);

    Color getColor(ColorIndex index) const;

private:
    Color m_colors[16];
};

}




