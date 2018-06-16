#pragma once

#include <vector>
#include <algorithm>

#include "IElement.h"

namespace wce {

class BaseScript {
public:
    virtual ~BaseScript() = 0;

    virtual void run() final;

    virtual void runAppend(bool clearBefore) final;

protected:
    template<class TElement, class ...Args>
    TElement &makeElement(Args ...args);

    template<class TElement>
    bool removeElement(const TElement &elem);

    void abort();

    bool isAborted() const;

    void onRun();

    virtual void onBeforeRun() { };

    virtual void onAfterRun() { };

private:
    std::vector<IElement *> m_elements;
    bool m_aborted = false;
};

template<class TElement, class ...Args>
TElement &BaseScript::makeElement(Args ...args) {
    auto element = new TElement(args...);
    m_elements.push_back(static_cast<IElement *>(element));
    return *element;
}

template<class TElement>
bool BaseScript::removeElement(const TElement &elem) {
    auto baseElem = static_cast<IElement *>(*elem);
    auto find = std::find(m_elements.cbegin(), m_elements.cend(), baseElem);
    if (find != m_elements.cend()) {
        m_elements.erase(find);
        return true;
    }
    return false;
}

}



