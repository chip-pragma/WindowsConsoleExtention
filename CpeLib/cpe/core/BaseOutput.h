#pragma once

#include "OutputFormat.h"

namespace cpe::core {

/**
 * Базовый класс вывода на консоль
 */
class BaseOutput {
public:
    BaseOutput();

    /**
     * Возвращает форматер вывода
     */
    const OutputFormat &getOutputFormat() const;

    /**
     * Задает форматер вывода
     */
    void setOutputFormat(const OutputFormat &outFormat);

    /**
     * Вывод данных
     */
    virtual void output() = 0;

protected:
    OutputFormat _outFormat;
};

}




