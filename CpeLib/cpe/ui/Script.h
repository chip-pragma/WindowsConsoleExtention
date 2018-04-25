#pragma once

#include <functional>

#include "cpe/Macros.h"
#include "ACommand.h"
#include "Buffer.h"

namespace cpe {

/**
 * Выполняемый скрипт из комманд
 * @tparam TProcessor Тип обработчика выполнения команд
 */
template<class TProcessor>
class Script {

public:
    explicit Script();

    ~Script();

    /**
     * Обработчик команд скрипта
     * @return
     */
    TProcessor *processor() const;

    /**
     * Создает команду указанного типа, добавляет в список выполняемых команд и возвращает ее
     * @tparam TCommand Тип команды
     */
    template<class TCommand>
    TCommand *add();

    /**
     * Запускает выполнение скрипта
     */
    void run() const;

private:
    // Обработчик команд
    TProcessor *mProcessor;
    // Список выполняемых команд
    std::vector<ACommand *> mItemList;
};

template<class TProcessor>
Script<TProcessor>::Script() {
    static_assert(
            std::is_base_of<AProcessor, TProcessor>::value,
            "'AProcessor' is not base for template-param 'TProcessor'");

    mProcessor = new TProcessor();
}

template<class TProcessor>
Script<TProcessor>::~Script() {
    for (auto item : mItemList)
        delete item;
    delete mProcessor;
}

template<class TProcessor>
void Script<TProcessor>::run() const {
    for (auto com : mItemList) {
        com->run();
    }
}

template<class TProcessor>
TProcessor *Script<TProcessor>::processor() const {
    return mProcessor;
}

template<class TProcessor>
template<class TCommand>
TCommand *Script<TProcessor>::add() {
    CPE__STATIC_CHECK_BASE_CLASS(ACommand, TCommand);

    auto *item = new TCommand();
    mItemList.push_back(static_cast<ACommand *>(item));
    return item;
}

}

