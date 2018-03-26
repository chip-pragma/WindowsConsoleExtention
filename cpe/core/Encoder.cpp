

#include "Encoder.h"

#include <Windows.h>

namespace cpe::utils {

Encoder::Encoder(unsigned int codePage) {
    _codePage = codePage;
}

std::string Encoder::encode(const std::wstring &decoded) const {
    // Получение кол-ва символов
    int length = WideCharToMultiByte(_codePage, 0, decoded.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (length <= 0)
        return "";
    // Создание char
    auto result = new char[length];
    // В char
    WideCharToMultiByte(_codePage, 0, decoded.c_str(), -1, result, length, nullptr, nullptr);

    return std::string(result);
}

std::wstring Encoder::decode(const std::string &encoded) const {
    // Получение кол-ва символов
    int length = MultiByteToWideChar(_codePage, 0, encoded.c_str(), -1, nullptr, 0);
    if (length <= 0)
        return L"";
    // Создание wide
    auto result = new wchar_t[length];
    // В wide
    MultiByteToWideChar(_codePage, 0, encoded.c_str(), -1, result, length);

    return std::wstring(result);
}

int Encoder::getCodePage() const {
    return _codePage;
}
}