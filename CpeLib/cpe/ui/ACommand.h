#pragma once

#include "cpe/ui/AProcessor.h"
#include "cpe/ui/Buffer.h"

namespace cpe {

/**
 * Базовый класс команды скрипта
 */
class ACommand {
public:
    /**
     * Запускает комманду
     */
    virtual void run() = 0;
};

}


