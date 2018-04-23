#pragma once

#include "AElement.h"

namespace cpe {

template<class TController>
class AScript {
public:
    AScript();

    ~AScript();

    virtual TController &controller() const final;

    virtual void run() final;

protected:

    virtual void initialize(ElementList &elemList) = 0;

private:
    TController *mController;
    ElementList mElementList;
    bool mFirstLaunch = true;
    cpe::Buffer *mBuffer;
};

template<class TController>
AScript<TController>::AScript() {
    static_assert(
            std::is_base_of<AController, TController>::value,
            "'AController' is not base for template-param 'TController'");

    mController = new TController();
    mBuffer = new cpe::Buffer();
}

template<class TController>
AScript<TController>::~AScript() {
    for (auto elem : mElementList) {
        delete elem;
    }
    delete mController;
    delete mBuffer;
}

template<class TController>
TController &AScript<TController>::controller() const {
    return *mController;
}

template<class TController>
void AScript<TController>::run() {
    if (mFirstLaunch) {
        initialize(mElementList);
        mFirstLaunch = false;
    }

    for (auto elem : mElementList) {
        elem->run(*mController, *mBuffer);
        // TODO Каждый элемент возвращает отрисованный буффер. А Script его уже flush'ит
        mBuffer->flush();
    }
}

}

