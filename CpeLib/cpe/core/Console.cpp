#include "Console.h"

namespace cpe::core::console {

void pause() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    system("pause");
#endif
}

void clear() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    system("cls");
#endif
}

void setTitle(const std::wstring &title) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    SetConsoleTitleW(title.c_str());
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
    return (bool) SetConsoleScreenBufferSize(
            _winapi::getOutputHandle(),
            size.toPlatform());
#endif
}

Point getBufferSize() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::getBufferInfo();
    return Point(info.dwSize);
#endif
}

bool setCursorPosition(const Point &size) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleCursorPosition(
            _winapi::getOutputHandle(),
            size.toPlatform());
#endif
}

Point getCursorPosition() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::getBufferInfo();
    return Point(info.dwCursorPosition);
#endif
}

bool moveCursor(const Point &vector) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    return setCursorPosition(
            getCursorPosition() + vector);

#endif
}

bool setForeColor(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    auto attr = (info.wAttributes & ~(WORD) 0b1111) | color.toPlatform();
    return (bool) SetConsoleTextAttribute(
            _winapi::getOutputHandle(),
            attr);

#endif
}

Color getForeColor() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    return Color(info.wAttributes);

#endif
}

bool setBackColor(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    auto attr = (info.wAttributes & ~((WORD) 0b1111 << 4)) | (color.toPlatform() << 4);
    return (bool) SetConsoleTextAttribute(
            _winapi::getOutputHandle(),
            attr);

#endif
}

Color getBackColor() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    return Color(info.wAttributes >> 4);

#endif
}

void swapOutputColors() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto back = getBackColor();
    auto fore = getForeColor();
    setBackColor(fore);
    setForeColor(back);

#endif
}

}