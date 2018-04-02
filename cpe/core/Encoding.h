

#ifndef PROJECT_ENCODING_H
#define PROJECT_ENCODING_H

#include <string>

namespace cpe::core::encoding {

/// Кодирует исходную последовательность байтов (wchar_t) в строку (string)
/// \param cpTo Кодировка, в которую кодируется последовательность байт
/// \param decoded Последовательность байтов
/// \return Кодированную строку
std::string encode(uint32_t cpTo, const std::wstring &decoded);

/// Декодирует исходную строку (string) в последовательность байт (wchar_t)
/// \param cpFrom Кодировка исходной строки
/// \param encoded Декодируемая исходная строка
/// \return Декодированая последовательность байт
std::wstring decode(uint32_t cpFrom, const std::string &encoded);

}

#endif //PROJECT_ENCODING_H
