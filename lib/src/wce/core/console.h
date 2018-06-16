#pragma once
#include <string>
#include <cstdint>

#include "Point.h"
#include "ColorTable.h"

namespace wce::console {

enum WceStdColors {
    cBlack,
    cRed,
    cGreen,
    cYellow,
    cBlue,
    cPurple,
    cTeal,
    cGray,
    cGrayLt,
    cRedLt,
    cGreenLt,
    cYellowLt,
    cBlueLt,
    cPurpleLt,
    cTealLt,
    cWhite
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
