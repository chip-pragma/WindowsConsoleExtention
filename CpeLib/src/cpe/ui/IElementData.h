#pragma once

namespace cpe {

class IElementData {
public:
    virtual ~IElementData() { }

    virtual const bool& getVisible() const = 0;

    virtual bool& getVisible() = 0;
};

}




