#pragma once

namespace cpe {

class IElementData {
public:
    virtual ~IElementData() { }

    virtual const bool &getVisible() const = 0;

    virtual void setVisible(bool value) = 0;

    virtual const bool &isCallPause() const = 0;

    virtual void setCallPause(bool value) = 0;
};

}




