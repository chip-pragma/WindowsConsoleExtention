#pragma once

#include "cpe/core/KeyType.h"
#include "InputFormat.h"

namespace cpe::ui {

using namespace cpe::core;

/**
 * Базовый класс ввода с клавиатуры
 */
class BaseInput {
public:
    BaseInput();

    /**
     * Запуск чтения
     */
    void read();

    /**
     * Возвращает форматер ввода
     */
    const InputFormat &getInputFormat() const;

    /**
     * Задает форматер ввода
     */
    void setInputFormat(const InputFormat &inFormat);

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
    void finishRead();

private:
    bool _readFinished;
    InputFormat _inFormat;
};

}
