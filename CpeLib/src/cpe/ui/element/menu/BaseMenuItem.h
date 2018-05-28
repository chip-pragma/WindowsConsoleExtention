#pragma once

#include "IMenuItem.h"

namespace cpe {

class BaseMenuItem : public IMenuItem {
public:
    const bool &getVisible() const override;

    bool &getVisible() override;

    const StyledText &getText() const;

    StyledText &getText();

protected:
    StyledText mText;
    bool mVisible = true;
};

}


