#pragma once

#include <string>

#include "WriterBase.h"
#include "cpe/ui/IInitializer.h"
#include "cpe/ui/style/BorderStyle.h"
#include "cpe/ui/output/StyledBorder.h"
#include "cpe/ui/output/StyledText.h"
#include "cpe/ui/output/StyledChar.h"
#include "cpe/ui/output/Buffer.h"

namespace cpe {

#undef MessageBox

class Notification : public WriterBase {
public:
    class Initializer : public IInitializer {
    public:
        explicit Initializer(Notification &element);

        StyledBorder &border();

        Nullable<StyledText> &caption();

        StyledText &message();

        Nullable<StyledChar> &icon();

        bool is_wait() const;

        void wait(bool wait);

    private:
        Notification &mElement;
    };

    Notification();

    ~Notification() override;

    const StyledBorder &border() const;

    StyledBorder &border();

    const Nullable<StyledText> &caption() const;

    Nullable<StyledText> &caption();

    const StyledText &message() const;

    StyledText &message();

    const Nullable<StyledChar> &icon() const;

    Nullable<StyledChar> &icon();

    bool is_wait() const;

    void wait(bool wait);

    void draw(Buffer &cvs) override;

    void output_to(std::ostream &outStream, const Point &size) override;

private:
    StyledBorder mBorder;
    Nullable<StyledChar> mIcon;
    Nullable<StyledText> mCaption;
    StyledText mMessage;
    bool mWait = false;
};



}




