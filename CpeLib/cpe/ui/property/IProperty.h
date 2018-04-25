#pragma once

namespace cpe {

class AProperties;

/**
 * Интерфейс для реализации свойств в наследниках класса AProperties
 */
class IProperty {
    friend class cpe::AProperties;

public:
    virtual ~IProperty() {

    };

protected:
    explicit IProperty(AProperties *owner);

    AProperties *mOwner;
};

}




