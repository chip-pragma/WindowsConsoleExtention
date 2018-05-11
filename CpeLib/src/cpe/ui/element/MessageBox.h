#pragma once

#include <string>

#include "ElementBase.h"
#include "cpe/ui/style/DualBorder.h"
#include "cpe/ui/style/Border.h"

namespace cpe {

#undef MessageBox

class MessageBox : public ElementBase {
public:
    MessageBox();

    const DualBorder& border_style() const;

    void border_style(const DualBorder& db);

    const std::string& caption() const;

    void caption(const std::string& caption);

    const std::string& text() const;

    void text(const std::string& text);

    const Nullable<StyledChar>& icon() const;

    Nullable<StyledChar>& icon();

    void icon(const Nullable<StyledChar>& icon);

    void draw(TextCanvas &canvas) override;

private:
    Border mBorder;
    Nullable<StyledChar> mIcon;
    std::string mCaption;
    std::string mText;
};

}




