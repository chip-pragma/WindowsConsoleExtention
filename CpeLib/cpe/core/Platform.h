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
#include "KeyType.h"

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
 * Получает код ввода с клавиатуры и определяет символ или команду, связанную с данной клавишей
 * @param keyType [<i>out</i>] Тип символ или команда клавиши
 * @param sym [<i>out</i>] Полученный символ или команда
 * @return В случае успеха 0. Иначе код ошибки платформы.
 */
unsigned int getKey(KeyType &keyType, char& sym);

}
