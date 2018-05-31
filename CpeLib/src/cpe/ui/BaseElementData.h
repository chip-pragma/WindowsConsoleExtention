#pragma once

#include "IElementData.h"

namespace cpe {

class BaseElementData : public IElementData {
public:
    ~BaseElementData() override;

    const bool &getVisible() const override;

    void setVisible(bool value) override;

    const bool &isCallPause() const override;

    void setCallPause(bool value) override;

protected:
    bool mVisible = true;
    bool mCallPause = false;
};

}




