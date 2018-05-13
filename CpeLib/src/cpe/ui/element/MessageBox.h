#pragma once

#include <string>

#include "ElementBase.h"
#include "cpe/ui/style/Border.h"
#include "cpe/ui/write/StyledBorder.h"

namespace cpe {

#undef MessageBox

class MessageBox : public ElementBase {
public:
    MessageBox();

    const StyledBorder & border() const;

    StyledBorder& border();

    const StyledText& caption() const;

    StyledText& caption();

    const StyledText& message() const;

    StyledText& message();

    const Nullable<StyledChar>& icon() const;

    Nullable<StyledChar>& icon();

    void draw(Buffer &canvas) override;

private:
    StyledBorder mBorder;
    Nullable<StyledChar> mIcon;
    StyledText mCaption;
    StyledText mMessage;
};

}




