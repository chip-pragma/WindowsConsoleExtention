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

bool input_cp(uint32_t codePage);

bool output_cp(uint32_t codePage);

uint32_t input_cp();

uint32_t output_cp();

bool window_size(const Point &size);

Point window_size();

bool cursor_position(const Point &pos);

Point cursor_position();

bool move_cursor(const Point &vector);

bool foreground(const Color &color);

Color foreground();

bool background(const Color &color);

Color background();

void swap_writer_colors();

}
