#pragma once

#include "IElementData.h"

namespace cpe {

class BaseElementData : public IElementData {
public:
    ~BaseElementData() override;

    const bool &getVisible() const override;

    bool &getVisible() override;

protected:
    bool mVisible = true;
};

}




