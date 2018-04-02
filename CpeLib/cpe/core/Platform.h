#pragma once

/**
 * ОПРЕДЕЛЕНИЕ ПЛАТФОРМЫ
 */
#if defined(__WIN32__) || defined(__MINGW32__)
#define CPE_PLATFORM_IS_WINDOWS
#endif

/**
 * ВКЛЮЧЕНИЕ ПЛАТФОРМОЗАВИСИМЫХ ЗАГОЛОВКОВ
 */
#if defined(CPE_PLATFORM_IS_WINDOWS)

#include <Windows.h>
typedef COORD PlatformPoint;

#endif

#include "Point.h"

namespace cpe::core::platform {

/**
 * Приведение типов Point в платформозависимый COORD
 * @param point Объект Point для приведения
 */
PlatformPoint toPlatformPoint(const Point &point);

/**
 * Приведение типов платформозависимый COORD в Point
 * @param point Объект COORD для приведения
 */
Point toCpePoint(const PlatformPoint &coord);

}
