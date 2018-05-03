#include "terminal.h"
#include "cpe/utils/text.h"
#include "cpe/utils/Convert.h"

namespace cpe::term {

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

void title(const std::string &title) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    SetConsoleTitleA(title.c_str());
#endif
}

std::string title() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    char title[MAX_PATH];
    GetConsoleTitle(title, MAX_PATH);
    return std::string(title);
#endif
}

bool inputCp(uint32_t codePage) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleCP(codePage);
#endif
}

bool outputCp(uint32_t codePage) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleOutputCP(codePage);
#endif
}

uint32_t inputCp() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return GetConsoleCP();
#endif
}

uint32_t outputCp() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return GetConsoleOutputCP();
#endif
}

bool windowSize(const Point &size) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleScreenBufferSize(
            _winapi::getOutputHandle(),
            size.toPlatform());
#endif
}

Point windowSize() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::getBufferInfo();
    return Point(info.dwSize);
#endif
}

bool cursorPosition(const Point &size) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleCursorPosition(
            _winapi::getOutputHandle(),
            size.toPlatform());
#endif
}

Point cursorPosition() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::getBufferInfo();
    return Point(info.dwCursorPosition);
#endif
}

bool moveCursor(const Point &vector) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    return cursorPosition(
            cursorPosition() + vector);

#endif
}

bool foreground(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    auto attr = (info.wAttributes & ~(WORD) 0b1111) | color.toPlatform();
    return (bool) SetConsoleTextAttribute(
            _winapi::getOutputHandle(),
            attr);

#endif
}

Color foreground() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    return Color(info.wAttributes);

#endif
}

bool background(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    auto attr = (info.wAttributes & ~((WORD) 0b1111 << 4)) | (color.toPlatform() << 4);
    return (bool) SetConsoleTextAttribute(
            _winapi::getOutputHandle(),
            attr);

#endif
}

Color background() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    return Color(info.wAttributes >> 4);

#endif
}

void swapWriterColors() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto back = background();
    auto fore = foreground();
    background(fore);
    foreground(back);

#endif
}

}