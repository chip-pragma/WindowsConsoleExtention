#pragma once

#include <Windows.h>
#include <cstdint>

#include "cpe/core/draw/Point.h"
#include "cpe/core/draw/Color.h"

namespace _winapi {


namespace {

enum class BitColor : uint8_t {
    RED = 2,
    GREEN = 1,
    BLUE = 0
};

SHORT buffer_attribute_color_component(uint8_t component, BitColor comp) noexcept {
    if (component < 64)
        return 0;
    else if (component <= 192)
        return SHORT(1) << static_cast<SHORT>(comp);
    else
        return SHORT(8) | (SHORT(1) << static_cast<SHORT>(comp));
}

}

inline cpe::Point to_point(const COORD &coord) {
    return cpe::Point(coord.X, coord.Y);
}

inline COORD from_point(const cpe::Point &point) {
    return COORD{
            .X = static_cast<SHORT>(point.getX()),
            .Y = static_cast<SHORT>(point.getY())
    };
}

inline cpe::Color to_color(SHORT bufferAttributes) {
    cpe::Color result;
    const uint8_t MIN = 128;
    const uint8_t PLUS = 127;
    auto i = MIN;
    if ((bufferAttributes & 8) == 8)
        i += PLUS;
    if ((bufferAttributes & 4) == 4)
        result.getR(i);
    if ((bufferAttributes & 2) == 2)
        result.getG(i);
    if ((bufferAttributes & 1) == 1)
        result.getB(i);
    return result;
}

inline SHORT from_color(cpe::Color color) {
    SHORT pc =
            buffer_attribute_color_component(color.getR(), BitColor::RED)
            | buffer_attribute_color_component(color.getG(), BitColor::GREEN)
            | buffer_attribute_color_component(color.getB(), BitColor::BLUE);
    return pc;
}

inline HANDLE output_handle() noexcept {
    return ::GetStdHandle(STD_OUTPUT_HANDLE);
}

inline HANDLE input_handle() noexcept {
    return ::GetStdHandle(STD_INPUT_HANDLE);
}

inline CONSOLE_SCREEN_BUFFER_INFO buffer_info() noexcept {
    CONSOLE_SCREEN_BUFFER_INFO info;
    ::GetConsoleScreenBufferInfo(
            output_handle(),
            &info);
    return info;
}
}