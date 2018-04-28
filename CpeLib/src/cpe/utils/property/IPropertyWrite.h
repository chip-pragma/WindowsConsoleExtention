#pragma once

#include "IPropertyRead.h"

namespace cpe {

template<class TValue>
class IPropertyWrite {

public:
    /**
     * Задает значение свойства
     */
    virtual void operator()(const TValue &value) = 0;

    /**
     * Задает значение свойства из другого свойства
     */
    virtual void operator()(IPropertyRead &prop) = 0;

};

}