#pragma once

#include "platform/platform.h"

#include <string>
#include <cstdint>

#include "cpe/core/draw/Point.h"
#include "cpe/core/draw/Color.h"

namespace cpe::term {

void callPause();

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

bool setForeground(const Color &color);

Color getForeground();

bool setBackground(const Color &color);

Color getBackground();

}
