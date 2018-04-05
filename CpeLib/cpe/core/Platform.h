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
#include <conio.h>

typedef COORD PlatformPoint;
typedef unsigned short PlatformColor;

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

/**
 * Получает символ нажатой клавиши (только <code>keyOrChar</code>) или код комманды (модификатор <code>keyOrChar</code> и код <code>command</code>), связанной с ней.
 * @param keyOrChar <i>[out]<i/> символ или модификатор
 * @param command <i>[out]<i/> код команды
 * @return Если успешно клавиша считана - true. Иначе false.
 */
bool getKey(char* keyOrChar, char* command);

}
