#include "Encoding.h"
#include "Platform.h"

namespace cpe::core::encoding {

std::string decode(uint32_t cpTo, const std::wstring &str) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    // Получение кол-ва символов
    int length = WideCharToMultiByte(cpTo, 0, str.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (length <= 0)
        return "";
    // Создание char
    auto result = new char[length];
    // В char
    WideCharToMultiByte(cpTo, 0, str.c_str(), -1, result, length, nullptr, nullptr);

    return std::string(result);

#endif
}

std::wstring toWChar(uint32_t cpFrom, const std::string &bytes) {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    // Получение кол-ва символов
    int length = MultiByteToWideChar(cpFrom, 0, bytes.c_str(), -1, nullptr, 0);
    if (length <= 0)
        return L"";
    // Создание wide
    auto result = new wchar_t[length];
    // В wide
    MultiByteToWideChar(cpFrom, 0, bytes.c_str(), -1, result, length);

    return std::wstring(result);

#endif
}

}
