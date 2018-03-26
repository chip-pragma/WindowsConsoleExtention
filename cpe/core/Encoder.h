

#ifndef PROJECT_ENCODER_H
#define PROJECT_ENCODER_H

#include <string>

namespace cpe::utils {

/**
 * Кодирование и декодирование строк
 */
class Encoder {
public:
    Encoder() = delete;

    /**
     * Создает кодировщик с заданной кодовой страницей (кодировкой)
     * @param codePage Кодировка
     */
    explicit Encoder(unsigned int codePage);

    /**
     * Кодирует исходную последовательность байтов (wchar_t) в строку (string)
     * @param decoded Последовательность байт
     * @return Кодированная строка
     */
    std::string encode(const std::wstring &decoded) const;

    /**
     * Декодирует исходную строку (string) в последовательность байт (wchar_t)
     * @param encoded Строка
     * @return Декодированная последовательность байт
     */
    std::wstring decode(const std::string &encoded) const;

    /**
     * Возвращает используемую кодовую страницу (кодировку)
     */
    int getCodePage() const;

private:
    unsigned int _codePage;
};

}

#endif //PROJECT_ENCODER_H
