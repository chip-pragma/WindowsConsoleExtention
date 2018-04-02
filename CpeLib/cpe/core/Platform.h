#pragma once

/**
 * ОПРЕДЕЛЕНИЕ ПЛАТФОРМЫ
 */
#if defined(__WIN32__) || defined(__MINGW32__)
/// Платформа Windows
#define CPE_PLATFORM_IS_WINDOWS
#endif

/**
 * ВКЛЮЧЕНИЕ ПЛАТФОРМОЗАВИСИМЫХ ЗАГОЛОВКОВ
 */
#if defined(CPE_PLATFORM_IS_WINDOWS)

#include <Windows.h>
#include <cstdint>

typedef COORD PlatformPoint;
typedef uint16_t PlatformColor;

#endif

#include "Point.h"
#include "Color.h"

namespace cpe::core::platform {

/**
 * Приведение типов координат (CPE => Platform)
 */
PlatformPoint toPlatformPoint(const Point &point);

/**
 * Приведение типов координат (Platform => CPE)
 */
Point toCpePoint(const PlatformPoint &coord);

/**
 * Приведение типов цвета (CPE => Platform)
 */
PlatformColor toPlatformColor(const Color &color);

/**
 * Приведение типов цвета (Platform => CPE)
 */
Color toCpeColor(const PlatformColor& color);

}
