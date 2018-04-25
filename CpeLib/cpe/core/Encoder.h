#pragma once

#include <string>

#include "cpe/Platform.h"

namespace cpe {

/**
* Кодировки
*/
enum class Encoding : uint32_t {
    UTF8 = 65001,
    CP866 = 866,
    CP1551 = 1251
};

/**
 * Кодировщик строк
 * @tparam CodePage Кодовая страница (кодировака), с которой работает кодировщик
 */
template<Encoding CodePage>
class Encoder {
public:
    /**
     * Декодирет строку в последовательность "широких байтов"
     * @param str декодируемая строка
     * @return декодированная последовательность "широких байтов"
     */
    std::wstring from(const std::string &str) const;

    /**
     * Кодирует последовательность "широких байтов" в строку
     * @param bytes кодируемая последовательность "широких байтов"
     * @return кодированную строку
     */
    std::string to(const std::wstring &bytes) const;
};

template<Encoding CodePage>
std::wstring Encoder<CodePage>::from(const std::string &str) const {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    // Получение кол-ва символов
    int length = MultiByteToWideChar(static_cast<uint32_t>(CodePage), 0, str.c_str(), -1, nullptr, 0);
    if (length <= 0)
        return L"";
    // Создание wide
    auto result = new wchar_t[length];
    // В wide
    MultiByteToWideChar(static_cast<uint32_t>(CodePage), 0, str.c_str(), -1, result, length);

    return std::wstring(result);

#endif
}

template<Encoding CodePage>
std::string Encoder<CodePage>::to(const std::wstring &bytes) const {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    // Получение кол-ва символов
    int length = WideCharToMultiByte(static_cast<uint32_t>(CodePage), 0, bytes.c_str(), -1, nullptr, 0, nullptr,
                                     nullptr);
    if (length <= 0)
        return "";
    // Создание char
    auto result = new char[length];
    // В char
    WideCharToMultiByte(static_cast<uint32_t>(CodePage), 0, bytes.c_str(), -1, result, length, nullptr, nullptr);

    return std::string(result);

#endif
}

}
