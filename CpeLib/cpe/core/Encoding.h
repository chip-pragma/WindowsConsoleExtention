

#ifndef PROJECT_ENCODING_H
#define PROJECT_ENCODING_H

#include <string>

namespace cpe::core::encoding {

/**
 * Кодирует исходную последовательность байтов (wchar_t) в строку (string)
 * @param cpTo Кодировка, в которую кодируется последовательность байт
 * @param str Последовательность байтов
 * @return Кодированную строку
 */
std::string fromWideChar(uint32_t cpTo, const std::wstring &str);

/**
 * Декодирует исходную строку (string) в последовательность байт (wchar_t)
 * @param cpFrom Кодировка исходной строки
 * @param bytes Декодируемая исходная строка
 * @return Декодированая последовательность байт
 */
std::wstring toWideChar(uint32_t cpFrom, const std::string &bytes);

}

#endif //PROJECT_ENCODING_H
