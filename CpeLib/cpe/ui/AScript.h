#pragma once

#include <functional>

#include "cpe/macros.h"
#include "ACommand.h"
#include "AContainer.h"
#include "AProcessor.h"

namespace cpe {

/**
 * Выполняемый скрипт из комманд
 * @tparam TProcessor Тип обработчика выполнения команд
 */
template<class TProcessor>
class AScript : protected AContainer {

public:
    explicit AScript();

    virtual ~AScript() override;

    /**
     * Обработчик команд скрипта
     * @return
     */
    virtual TProcessor *processor() const final;

    /**
     * Запускает выполнение скрипта
     */
    void run() const;

private:
    // Обработчик команд
    TProcessor *const mProcessor;
};

template<class TProcessor>
AScript<TProcessor>::AScript() : mProcessor(new TProcessor()) {
    static_assert(
            std::is_base_of<AProcessor, TProcessor>::value,
            "'AProcessor' is not base for template-param 'TProcessor'");
}

template<class TProcessor>
AScript<TProcessor>::~AScript() {
    delete mProcessor;
}

template<class TProcessor>
void AScript<TProcessor>::run() const {
    Buffer buf;
    std::vector<AReader *> readers;
    for (auto com : AContainer::items()) {
        com->run(buf, readers);
        buf.flush();
    }
}

template<class TProcessor>
TProcessor *AScript<TProcessor>::processor() const {
    return mProcessor;
}

}

