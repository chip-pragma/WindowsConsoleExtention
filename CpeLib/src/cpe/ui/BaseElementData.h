#pragma once

#include "IElementData.h"

namespace cpe {

class BaseElementData : public IElementData {
public:
    ~BaseElementData() override;

    const bool &visible() const override;

    bool &visible() override;

protected:
    bool mVisible = true;
};

}




