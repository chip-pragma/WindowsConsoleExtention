#include "Console.h"
#include "Platform.h"

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
    return (bool) SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), platform::toPlatformPoint(size));
#endif
}

Point getBufferSize() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(
            GetStdHandle(STD_OUTPUT_HANDLE),
            &info);
    return platform::toCpePoint(info.dwSize);
#endif
}

bool setCursorPosition(const Point &size) {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    return (bool) SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            platform::toPlatformPoint(size));
#endif
}

Point getCursorPosition() {
#if defined(CPE_PLATFORM_IS_WINDOWS)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info{};
    GetConsoleScreenBufferInfo(
            GetStdHandle(STD_OUTPUT_HANDLE),
            &info);
    return platform::toCpePoint(info.dwCursorPosition);
#endif
}

bool setForeColor(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    return (bool) SetConsoleTextAttribute(
            GetStdHandle(STD_OUTPUT_HANDLE),
            platform::toPlatformColor(color));

#endif
}

Color getForeColor() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    CONSOLE_SCREEN_BUFFER_INFO info;
    auto b = (bool)GetConsoleScreenBufferInfo(
            GetStdHandle(STD_OUTPUT_HANDLE),
            &info);
    return platform::toCpeColor(info.wAttributes);

#endif
}

bool setBackColor(const Color &color) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    return (bool) SetConsoleTextAttribute(
            GetStdHandle(STD_OUTPUT_HANDLE),
            platform::toPlatformColor(color) << 4u);

#endif
}

Color getBackColor() {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    CONSOLE_SCREEN_BUFFER_INFO info;
    auto b = (bool)GetConsoleScreenBufferInfo(
            GetStdHandle(STD_OUTPUT_HANDLE),
            &info);
    return platform::toCpeColor(info.wAttributes >> 4u);

#endif
}

}