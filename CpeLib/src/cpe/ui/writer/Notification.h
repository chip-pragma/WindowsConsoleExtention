#pragma once

#include <string>

#include "IWriter.h"
#include "cpe/ui/IInitializer.h"
#include "cpe/ui/style/Border.h"
#include "cpe/ui/output/StyledBorder.h"
#include "cpe/ui/output/StyledText.h"
#include "cpe/ui/output/StyledChar.h"
#include "cpe/ui/output/Buffer.h"

namespace cpe {

#undef MessageBox

class Notification : public IWriter {
public:
    class Initializer : public IInitializer {
    public:
        explicit Initializer(Notification &element);

        StyledBorder &border();

        Nullable<StyledText> &caption();

        StyledText &message();

        Nullable<StyledChar> &icon();

    private:
        Notification &mElement;
    };

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



}




