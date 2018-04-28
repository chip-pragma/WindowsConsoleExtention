#pragma once

namespace cpe {

template<class TValue>
class IPropertyRead {

public:

    /**
     * Возвращает значение свойства
     */
    virtual TValue &operator()() const = 0;

};

}
