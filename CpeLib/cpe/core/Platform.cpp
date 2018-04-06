#include "Platform.h"

namespace cpe::core::platform {

namespace {

#if defined(CPE_PLATFORM_IS_WINDOWS)

/// функции для Windows API
namespace _winapi {

/**
 * Компоненты цвета в WinAPI
 */
enum class ColorComponent : uint8_t {
    RED = 2,
    GREEN = 1,
    BLUE = 0
};

/**
 * Получает битовое "слово" компонента цвета из значения [0..255]
 * @param component Значение компонента цвета [0..255]
 * @param comp Компонент цвета
 * @return битовое "слово" компонента цвета
 */
PlatformColor getColorComponentBit(uint8_t component, ColorComponent comp) {
    if (component < 64)
        return 0;
    else if (component <= 192)
        return (PlatformColor) 1 << (uint8_t) comp;
    else
        return (PlatformColor) (8u | (1u << (uint8_t) comp));
}

}

#endif

}

PlatformPoint toPlatformPoint(const Point &point) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    COORD coord{
            .X = point.x,
            .Y = point.y
    };
    return coord;
#endif
}

Point toCpePoint(const PlatformPoint &coord) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return Point(coord.X, coord.Y);
#endif
}

PlatformColor toPlatformColor(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    PlatformColor pc =
            _winapi::getColorComponentBit(color.getR(), _winapi::ColorComponent::RED)
            | _winapi::getColorComponentBit(color.getG(), _winapi::ColorComponent::GREEN)
            | _winapi::getColorComponentBit(color.getB(), _winapi::ColorComponent::BLUE);
    return pc;
#endif
}

Color toCpeColor(const PlatformColor &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    const uint8_t MIN = 128u;
    const uint8_t PLUS = 127;
    auto i = MIN;
    if ((color & 8u) == 8u)
        i += PLUS;
    Color c;
    if ((color & 4u) == 4u)
        c.setR(i);
    if ((color & 2u) == 2u)
        c.setG(i);
    if ((color & 1u) == 1u)
        c.setB(i);

    return c;
#endif
}

unsigned int getKey(KeyType &keyType, char& sym) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    keyType = KeyType::Symbol;
    SetLastError(0u);
    sym = (char)getch();
    auto hit = _kbhit();
    if (hit)
        keyType = (KeyType)getch();
    return GetLastError();

#endif
}

}