#pragma once

#include "cpe/core/KeyType.h"
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

protected:
    /**
     * Получение символа
     * @param symbol полученный символ
     */
    virtual void onReceiveSymbol(const char &symbol) = 0;

    /**
     * Получение команды
     * @param command тип комманды
     */
    virtual void onReceiveCommand(const KeyType &command) = 0;

    /**
     * Ошибка при вводе
     */
    virtual void onReadingError() = 0;

    /**
     * Завершить чтение
     */
    virtual void finishRead() final;

private:
    bool _readFinished;
    InputFormat _inFormat;
};

}
