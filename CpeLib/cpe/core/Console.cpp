#include "Console.h"
#include "Platform.h"

namespace cpe::core::console {

namespace {

#if defined(CPE_PLATFORM_IS_WINDOWS)

namespace _winapi {

HANDLE getHandle() {
    return GetStdHandle(STD_OUTPUT_HANDLE);
}

CONSOLE_SCREEN_BUFFER_INFO getBufferInfo() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(
            getHandle(),
            &info);
    return info;
}

}

#endif

}

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

void setTitle(const std::string &title) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    SetConsoleTitle(title.c_str());
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
            _winapi::getHandle(),
            platform::toPlatformPoint(size));
#endif
}

Point getBufferSize() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::getBufferInfo();
    return platform::toCpePoint(info.dwSize);
#endif
}

bool setCursorPosition(const Point &size) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleCursorPosition(
            _winapi::getHandle(),
            platform::toPlatformPoint(size));
#endif
}

Point getCursorPosition() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    auto info = _winapi::getBufferInfo();
    return platform::toCpePoint(info.dwCursorPosition);
#endif
}

bool setForeColor(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    auto attr = (info.wAttributes & ~(WORD)0b1111) | platform::toPlatformColor(color);
    return (bool) SetConsoleTextAttribute(
            _winapi::getHandle(),
            attr);

#endif
}

Color getForeColor() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    return platform::toCpeColor(info.wAttributes);

#endif
}

bool setBackColor(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    auto attr = (info.wAttributes & ~((WORD)0b1111 << 4)) | (platform::toPlatformColor(color) << 4);
    return (bool) SetConsoleTextAttribute(
            _winapi::getHandle(),
            attr);

#endif
}

Color getBackColor() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    auto info = _winapi::getBufferInfo();
    return platform::toCpeColor(info.wAttributes >> 4);

#endif
}

}