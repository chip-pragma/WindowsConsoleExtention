#pragma once

#include "InputFormat.h"

namespace cpe::core {

/**
 * Базовый класс ввода с клавиатуры
 */
class BaseInput {
public:
    BaseInput();

    /**
     * Запуск чтения
     */
    virtual void startRead() final;

    /**
     * Возвращает форматер ввода
     */
    virtual const InputFormat &getInputFormat() const final;

    /**
     * Задает форматер ввода
     */
    virtual void setInputFormat(const InputFormat &inFormat) final;

    /**
     * Удаляет форматер ввода
     */
    virtual void cleanInputFormat() final;

protected:
    const InputFormat *_inFormat;

    /**
     * Получение символа
     * @param symbol полученный символ
     */
    virtual void onKeyRead(const char &symbol) = 0;

    /**
     * Ошибка при вводе
     */
    virtual void onReadingError(uint32_t errCode) = 0;

    /**
     * Завершить чтение
     */
    virtual void finishRead() final;

private:
    bool _readFinished;
};

}
