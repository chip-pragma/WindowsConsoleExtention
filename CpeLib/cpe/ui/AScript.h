#pragma once

#include <functional>

#include "cpe/Macros.h"
#include "cpe/ui/ACommand.h"

namespace cpe {

class AProcessor;

/**
 * Выполняемый скрипт из комманд
 * @tparam TProcessor Тип обработчика выполнения команд
 */
template<class TProcessor>
class AScript {

public:
    explicit AScript();

    virtual ~AScript() = 0;

    /**
     * Обработчик команд скрипта
     * @return
     */
    virtual TProcessor *processor() const final;

    /**
     * Запускает выполнение скрипта
     */
    void run() const;

protected:
    /**
* Создает команду указанного типа, добавляет в список выполняемых команд и возвращает ее
* @tparam TCommand Тип команды
*/
    template<class TCommand>
    TCommand *add();

private:
    // Обработчик команд
    TProcessor *const mProcessor;
    // Список выполняемых команд
    std::vector<ACommand *> mItemList;
};

template<class TProcessor>
AScript<TProcessor>::AScript() : mProcessor(new TProcessor()) {
    static_assert(
            std::is_base_of<AProcessor, TProcessor>::value,
            "'AProcessor' is not base for template-param 'TProcessor'");
}

template<class TProcessor>
AScript<TProcessor>::~AScript() {
    for (auto item : mItemList)
        delete item;
    delete mProcessor;
}

template<class TProcessor>
void AScript<TProcessor>::run() const {
    for (auto com : mItemList) {
        com->run();
    }
}

template<class TProcessor>
TProcessor *AScript<TProcessor>::processor() const {
    return mProcessor;
}

template<class TProcessor>
template<class TCommand>
TCommand *AScript<TProcessor>::add() {
    CPE__STATIC_CHECK_BASE_CLASS(ACommand, TCommand);

    auto *item = new TCommand();
    mItemList.push_back(static_cast<ACommand *>(item));
    return item;
}

}

