#pragma once

#include <string>
#include <cstdlib>

#include "Point.h"
#include "Color.h"

namespace cpe::term {

void pause();

void clear();

void title(const std::string &title);

std::string title();

bool inputCp(uint32_t codePage);

bool outputCp(uint32_t codePage);

uint32_t inputCp();

uint32_t outputCp();

bool windowSize(const Point &size);

Point windowSize();

bool cursorPosition(const Point &pos);

Point cursorPosition();

bool moveCursor(const Point &vector);

bool foreground(const Color &color);

Color foreground();

bool background(const Color &color);

Color background();

void swapWriterColors();

}
