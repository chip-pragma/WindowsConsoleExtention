#pragma once

#include "IMenuItem.h"

namespace cpe {

class BaseMenuItem : public IMenuItem {
public:
    const bool &getVisible() const override;

    void setVisible(bool vis) override;

    const StyledText &getText() const;

    StyledText &getTextRef();

protected:
    StyledText mText;
    bool mVisible = true;
};

}


