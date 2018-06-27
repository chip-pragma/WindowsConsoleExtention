#pragma once

#include <vector>
#include <algorithm>

#include "wce/core/functional/BaseDelegate.h"

namespace wce {

template<class TOwner, class ...TArgs>
class Event {
    friend TOwner;

public:
    using Handler = BaseDelegate<void, TArgs...>;

    ~Event();

    template<class TDelegate>
    void addHandler(const TDelegate &delegate);

    template<class TDelegate>
    void removeHandler(const TDelegate &delegate);

    void clearHandlers();

    template<class TDelegate>
    void operator+=(const TDelegate &delegate);

    template<class TDelegate>
    void operator-=(const TDelegate &delegate);

protected:
    virtual void fire(TArgs...args);

private:
    std::vector<Handler *> m_handlers;
};

template<class TOwner, class... TArgs>
Event<TOwner, TArgs...>::~Event() {
    clearHandlers();
}

template<class TOwner, class... TArgs>
template<class TDelegate>
void Event<TOwner, TArgs...>::addHandler(const TDelegate &delegate) {
    m_handlers.push_back(static_cast<Handler *>(new TDelegate(delegate)));
}

template<class TOwner, class... TArgs>
template<class TDelegate>
void Event<TOwner, TArgs...>::removeHandler(const TDelegate &delegate) {
    auto castedDelegate = static_cast<const Handler *>(&delegate);

    auto newEnd = std::remove_if(
        m_handlers.begin(), m_handlers.end(),
        [&](const Handler *handler) {
            if (*handler == *castedDelegate) {
                delete handler;
                return true;
            }
            return false;
        });
    m_handlers.erase(newEnd, m_handlers.end());
}

template<class TOwner, class... TArgs>
void Event<TOwner, TArgs...>::clearHandlers() {
    for (auto handler : m_handlers)
        delete handler;
    m_handlers.clear();
}

template<class TOwner, class... TArgs>
template<class TDelegate>
void Event<TOwner, TArgs...>::operator+=(const TDelegate &delegate) {
    addHandler(delegate);
}

template<class TOwner, class... TArgs>
template<class TDelegate>
void Event<TOwner, TArgs...>::operator-=(const TDelegate &delegate) {
    removeHandler(delegate);
}

template<class TOwner, class... TArgs>
void Event<TOwner, TArgs...>::fire(TArgs... args) {
    for (Handler *handler : m_handlers)
        handler->invoke(args...);
}

}


