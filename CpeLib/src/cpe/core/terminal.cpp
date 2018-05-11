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

bool buffer_size(const Size &size) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return static_cast<bool>(SetConsoleScreenBufferSize(
                _winapi::output_handle(),
                _winapi::from_point(size.to_point())));
#endif
}

Size buffer_size() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::buffer_info();
    return _winapi::to_point(info.dwSize).to_size();
#endif
}

bool cursor_position(const Point &point) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleCursorPosition(
            _winapi::output_handle(),
            _winapi::from_point(point));
#endif
}

Point cursor_position() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::buffer_info();
    return _winapi::to_point(info.dwCursorPosition);
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

    auto info = _winapi::buffer_info();
    auto attr = (info.wAttributes & ~uint16_t(0b1111)) | _winapi::from_color(color);
    return (bool) SetConsoleTextAttribute(
            _winapi::output_handle(),
            attr);

#endif
}

Color foreground() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::buffer_info();
    return _winapi::to_color(info.wAttributes);

#endif
}

bool background(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::buffer_info();
    auto attr = (info.wAttributes & (~uint16_t(0b1111) << 4)) | (_winapi::from_color(color) << 4);
    return (bool) SetConsoleTextAttribute(
            _winapi::output_handle(),
            attr);

#endif
}

Color background() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::buffer_info();
    return _winapi::to_color(info.wAttributes >> 4);

#endif
}

}