#pragma once

#include "cpe/ui/reader/AReader.h"
#include "Buffer.h"

namespace cpe {

/**
 * Базовый класс команды скрипта
 */
class ACommand {
public:
    /**
     * Запускает комманду
     */
    virtual void *run(Buffer &buf, std::vector<AReader *> &readers) = 0;
};

}


