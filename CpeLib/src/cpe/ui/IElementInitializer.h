#pragma once

namespace cpe {

class ElementBase;

class IController;

class IElementInitializer {
public:
    explicit IElementInitializer(ElementBase &element) { };

    virtual ~IElementInitializer() { }
};

}




