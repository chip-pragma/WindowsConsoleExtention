#pragma once

#include <windows.h>
#include <cstdint>

#include "wce/core/draw/Point.h"
#include "wce/core/draw/Color.h"

namespace _winapi {


namespace {

enum class BitColor : uint8_t {
    RED = 2,
    GREEN = 1,
    BLUE = 0
};

SHORT bufferAttributeColorComponent(uint8_t component, BitColor comp) noexcept {
    if (component < 64)
        return 0;
    else if (component <= 192)
        return SHORT(1) << static_cast<SHORT>(comp);
    else
        return SHORT(8) | (SHORT(1) << static_cast<SHORT>(comp));
}

}

inline wce::Point toPoint(const COORD &coord) {
    return wce::Point(coord.X, coord.Y);
}

inline COORD fromPoint(const wce::Point &point) {
    return COORD{
            .X = static_cast<SHORT>(point.getX()),
            .Y = static_cast<SHORT>(point.getY())
    };
}

inline wce::Color toColor(SHORT bufferAttributes) {
    wce::Color result;
    const uint8_t MIN = 128;
    const uint8_t PLUS = 127;
    auto i = MIN;
    if ((bufferAttributes & 8) == 8)
        i += PLUS;
    if ((bufferAttributes & 4) == 4)
        result.setR(i);
    if ((bufferAttributes & 2) == 2)
        result.setG(i);
    if ((bufferAttributes & 1) == 1)
        result.setB(i);
    return result;
}

inline SHORT fromColor(wce::Color color) {
    SHORT pc =
        bufferAttributeColorComponent(color.getR(), BitColor::RED)
            | bufferAttributeColorComponent(color.getG(), BitColor::GREEN)
            | bufferAttributeColorComponent(color.getB(), BitColor::BLUE);
    return pc;
}

inline HANDLE getOutputHandle() noexcept {
    return ::GetStdHandle(STD_OUTPUT_HANDLE);
}

inline HANDLE getInputHandle() noexcept {
    return ::GetStdHandle(STD_INPUT_HANDLE);
}

inline CONSOLE_SCREEN_BUFFER_INFO getBufferInfo() noexcept {
    CONSOLE_SCREEN_BUFFER_INFO info;
    ::GetConsoleScreenBufferInfo(
        getOutputHandle(),
            &info);
    return info;
}
}