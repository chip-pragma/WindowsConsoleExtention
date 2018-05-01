#pragma once

namespace cpe {

class PropertyProviderAbstract;

/**
 * Интерфейс для реализации свойств в наследниках класса AProperties
 */
class PropertyInterface {
    friend class PropertyProviderAbstract;

public:
    virtual ~PropertyInterface() { ; };
};

}




