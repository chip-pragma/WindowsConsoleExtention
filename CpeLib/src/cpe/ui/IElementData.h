#pragma once

namespace cpe {

class IElementData {
public:
    virtual ~IElementData() { }

    virtual const bool& visible() const = 0;

    virtual bool& visible() = 0;
};

}




