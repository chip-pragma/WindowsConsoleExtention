#include "Encoder.h"

namespace cpe {

Encoder::Encoder(Encoding encodingCp) : mCp(encodingCp) {

}

std::wstring Encoder::from(const std::string &str) const {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    // Получение кол-ва символов
    int length = MultiByteToWideChar(static_cast<uint32_t>(mCp), 0, str.c_str(), -1, nullptr, 0);
    if (length <= 0)
        return L"";
    // Создание wide
    auto result = new wchar_t[length];
    // В wide
    MultiByteToWideChar(static_cast<uint32_t>(mCp), 0, str.c_str(), -1, result, length);

    return std::wstring(result);

#endif
}

std::string Encoder::to(const std::wstring &bytes) const {
#if defined(CPE_PLATFORM_IS_WINDOWS)

    // Получение кол-ва символов
    int length = WideCharToMultiByte(static_cast<uint32_t>(mCp), 0, bytes.c_str(), -1, nullptr, 0, nullptr,
                                     nullptr);
    if (length <= 0)
        return "";
    // Создание char
    auto result = new char[length];
    // В char
    WideCharToMultiByte(static_cast<uint32_t>(mCp), 0, bytes.c_str(), -1, result, length, nullptr, nullptr);

    return std::string(result);

#endif
}



}
