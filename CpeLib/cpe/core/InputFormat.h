#pragma once

#include <string>

namespace cpe::core {

/**
 * Базовый класс форматера ввода.
 */
class InputFormat {
public:
    /**
     * Препроцессор ввода. Выполняется при каждом вводе печатного символа.
     * @param c Символ ввода
     * @return При успешном препроцессе true. Иначе false.
     */
    virtual bool preprocess(char &c) const = 0;
};

}




