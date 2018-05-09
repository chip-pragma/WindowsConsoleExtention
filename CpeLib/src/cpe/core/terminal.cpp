#include "terminal.h"
#include "cpe/tool/text.h"
#include "cpe/tool/Convert.h"

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

bool input_cp(uint32_t codePage) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleCP(codePage);
#endif
}

bool output_cp(uint32_t codePage) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleOutputCP(codePage);
#endif
}

uint32_t input_cp() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return GetConsoleCP();
#endif
}

uint32_t output_cp() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return GetConsoleOutputCP();
#endif
}

bool window_size(const Point &size) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleScreenBufferSize(
            _winapi::getOutputHandle(),
            size.to_platform());
#endif
}

Point window_size() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::getBufferInfo();
    return Point(info.dwSize);
#endif
}

bool cursor_position(const Point &size) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleCursorPosition(
            _winapi::getOutputHandle(),
            size.to_platform());
#endif
}

Point cursor_position() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::getBufferInfo();
    return Point(info.dwCursorPosition);
#endif
}

bool move_cursor(const Point &vector) {

#if defined(CPE_PLATFORM_IS_WINDOWS)
    return cursor_position(
            cursor_position() + vector);
#endif

}

bool foreground(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    auto attr = (info.wAttributes & ~(WORD) 0b1111) | color.to_platform();
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
    auto attr = (info.wAttributes & ~((WORD) 0b1111 << 4)) | (color.to_platform() << 4);
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

void swap_writer_colors() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto back = background();
    auto fore = foreground();
    background(fore);
    foreground(back);

#endif
}

}