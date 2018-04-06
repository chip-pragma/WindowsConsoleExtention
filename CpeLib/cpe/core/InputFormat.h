#pragma once

#include <string>

namespace cpe::core {

/**
 * Базовый класс форматера ввода.
 */
class InputFormat {
public:
    InputFormat();

    /**
     * Препроцессор ввода. Выполняется при каждом вводе печатного символа.
     * @param c Символ ввода
     * @return При успешном препроцессе true. Иначе false.
     */
    virtual bool preprocess(char &c) const;

    /**
     * Возвращает допустимые символы при вводе
     */
    const std::string &getAllowedChars() const;

    /**
     * Задает допустимые символы при вводе
     */
    void setAllowedChars(const std::string &allowedChars);

protected:
    /// Разрешенные символы для ввода
    std::string _allowedChars;

    /**
     * Проверяет, разрешен ли символ
     * @param c проверяемый символ
     */
    bool checkAllowChar(const char &c) const;
};

}




