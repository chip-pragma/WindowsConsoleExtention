#pragma once

namespace cpe {

class AProperties;

/**
 * Интерфейс для реализации свойств в наследниках класса AProperties
 */
class IProperty {
    friend class AProperties;

public:
    virtual ~IProperty() { ; };
};

}




