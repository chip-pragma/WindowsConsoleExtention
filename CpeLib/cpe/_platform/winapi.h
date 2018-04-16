#pragma once

#include <Windows.h>
#include <cstdint>

typedef COORD PlatformPoint;
typedef unsigned short PlatformColor;
typedef KEY_EVENT_RECORD PlatformKeyData;

/// функции Windows API
namespace _winapi {

/**
 * Компоненты цвета в WinAPI
 */
enum class BitColorComponent : uint8_t {
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
inline PlatformColor getColorComponentBit(uint8_t component, BitColorComponent comp) noexcept {
    if (component < 64)
        return 0;
    else if (component <= 192)
        return (PlatformColor) 1 << (uint8_t) comp;
    else
        return (PlatformColor) (8u | (1u << (uint8_t) comp));
}

/**
 * Возвращает дескриптор вывода консоли
 */
inline HANDLE getOutputHandle() noexcept {
    return GetStdHandle(STD_OUTPUT_HANDLE);
}

/**
 * Возвращает дескриптор ввода консоли
 */
inline HANDLE getInputHandle() noexcept {
    return GetStdHandle(STD_INPUT_HANDLE);
}

/**
 * Возвращает информацию о буфере вывода консоли
 * @return
 */
inline CONSOLE_SCREEN_BUFFER_INFO getBufferInfo() noexcept {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(
            getOutputHandle(),
            &info);
    return info;
}

}