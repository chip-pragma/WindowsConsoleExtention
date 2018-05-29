#include "terminal.h"
#include "Exception.h"
#include "cpe/tool/text.h"
#include "cpe/tool/Convert.h"

#include <cstdlib>

namespace cpe::term {

void callPause() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    system("pause");
#endif
}

void clear() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    system("cls");
#endif
}

void setTitle(const std::string &title) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    SetConsoleTitleA(title.c_str());
#endif
}

std::string getTitle() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    char title[MAX_PATH];
    GetConsoleTitle(title, MAX_PATH);
    return std::string(title);
#endif
}

bool setInputCp(uint32_t codePage) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleCP(codePage);
#endif
}

bool setOutputCp(uint32_t codePage) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleOutputCP(codePage);
#endif
}

uint32_t getInputCp() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return GetConsoleCP();
#endif
}

uint32_t getOutputCp() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return GetConsoleOutputCP();
#endif
}

bool setBufferSize(const Point &size) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    if (size.calcLocation() != Point::PL_SECTOR_I)
        throw Exception("Invalid width");

    return static_cast<bool>(SetConsoleScreenBufferSize(
        _winapi::getOutputHandle(),
                _winapi::fromPoint(size)));
#endif
}

Point getBufferSize() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::getBufferInfo();
    return _winapi::toPoint(info.dwSize);
#endif
}

bool setCursorPos(const Point &point) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleCursorPosition(
        _winapi::getOutputHandle(),
            _winapi::fromPoint(point));
#endif
}

Point getCursorPos() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::getBufferInfo();
    return _winapi::toPoint(info.dwCursorPosition);
#endif
}

bool setForeground(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    auto attr = (info.wAttributes & ~(uint16_t(0b1111))) | _winapi::fromColor(color);
    return (bool) SetConsoleTextAttribute(
        _winapi::getOutputHandle(),
            attr);

#endif
}

Color getForeground() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    return _winapi::toColor(info.wAttributes);

#endif
}

bool setBackground(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    auto attr = (info.wAttributes & (~(uint16_t(0b1111) << 4))) | (_winapi::fromColor(color) << 4);
    return (bool) SetConsoleTextAttribute(
        _winapi::getOutputHandle(),
            attr);

#endif
}

Color getBackground() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    return _winapi::toColor(info.wAttributes >> 4);

#endif
}

}