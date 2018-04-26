#pragma once

#include "cpe/macros.h"
#include "ACommand.h"

namespace cpe {

/**
 * Содержит набор комманд
 */
class AContainer {
public:
    virtual ~AContainer();

public:
    /**
    * Создает команду указанного типа, добавляет в список выполняемых команд и возвращает ее
    * @tparam TCommand Тип команды
    */
    template<class TCommand>
    TCommand *add();

protected:
    /**
     * Возвращает список комманд контейнера
     */
    const std::vector<ACommand *> &items() const;

private:
    // Список выполняемых команд
    std::vector<ACommand *> mItemList;
};

template<class TCommand>
TCommand *AContainer::add() {
    CPE_MACROS_StaticCheckBaseClass(ACommand, TCommand);

    auto *item = new TCommand();
    mItemList.push_back(static_cast<ACommand *>(item));
    return item;
}

}




