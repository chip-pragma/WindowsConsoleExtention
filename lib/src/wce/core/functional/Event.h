#pragma once

#include <vector>
#include <algorithm>

#include "BaseDelegate.h"

namespace wce {

template<class TOwner, class ...TArgs>
class Event {
    friend TOwner;

public:
    using Handler = BaseDelegate<void, TArgs...>;

    ~Event() {
        clearHandlers();
    }

    template<class TDelegate>
    void addHandler(const TDelegate &delegate) {
        m_handlers.push_back(static_cast<Handler *>(new TDelegate(delegate)));
    }

    template<class TDelegate>
    void removeHandler(const TDelegate &delegate) {
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

    void clearHandlers() {
        for (auto handler : m_handlers)
            delete handler;
        m_handlers.clear();
    }

    template<class TDelegate>
    void operator+=(const TDelegate &delegate) {
        addHandler(delegate);
    }

    template<class TDelegate>
    void operator-=(const TDelegate &delegate) {
        removeHandler(delegate);
    }

protected:
    virtual void invoke(TArgs &...args) {
        for (Handler *handler : m_handlers)
            handler->invoke(args...);
    }

private:
    std::vector<Handler *> m_handlers;
};

}


