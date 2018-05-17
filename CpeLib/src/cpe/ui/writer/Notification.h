#pragma once

#include <string>

#include "WriterBase.h"
#include "cpe/ui/IInitializer.h"
#include "cpe/ui/style/Border.h"
#include "cpe/ui/output/StyledBorder.h"

namespace cpe {

#undef MessageBox

class Notification : public WriterBase {
public:
    Notification();

    const StyledBorder &border() const;

    StyledBorder &border();

    const Nullable<StyledText> &caption() const;

    Nullable<StyledText> &caption();

    const StyledText &message() const;

    StyledText &message();

    const Nullable<StyledChar> &icon() const;

    Nullable<StyledChar> &icon();

    void draw(Buffer &cvs) override;

private:
    StyledBorder mBorder;
    Nullable<StyledChar> mIcon;
    Nullable<StyledText> mCaption;
    StyledText mMessage;
};

class NotificationInitializer : public IInitializer {
public:
    explicit NotificationInitializer(Notification &element);

    StyledBorder &border();

    Nullable<StyledText> &caption();

    StyledText &message();

    Nullable<StyledChar> &icon();

private:
    Notification &mElement;
};

}




