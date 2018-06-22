#pragma once
#include <string>
#include <cstdint>

#include "wce/core/graphics/Point.h"
#include "wce/core/graphics/ColorTable.h"

namespace wce::console {

enum WceStdColors {
    C_BLACK,
    C_DK_RED,
    C_DK_GREEN,
    C_DK_YELLOW,
    C_DK_BLUE,
    C_DK_PURPLE,
    C_DK_TEAL,
    C_LT_GRAY,
    C_DK_GRAY,
    C_LT_RED,
    C_LT_GREEN,
    C_LT_YELLOW,
    C_LT_BLUE,
    C_LT_PURPLE,
    C_LT_TEAL,
    C_WHITE
};

void waitAnyKey();

void clear();

void setTitle(const std::string &title);

std::string getTitle();

bool setInputCp(uint32_t codePage);

bool setOutputCp(uint32_t codePage);

uint32_t getInputCp();

uint32_t getOutputCp();

bool setBufferSize(const Point &size);

Point getBufferSize();

bool setCursorPos(const Point &pos);

Point getCursorPos();

bool setColorTable(const ColorTable &table);

ColorTable getColorTable();

bool resetColorTable();

bool setForeground(const ColorIndex &color);

ColorIndex getForeground();

bool setBackground(const ColorIndex &color);

ColorIndex getBackground();

}
