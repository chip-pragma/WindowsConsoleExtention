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

class Notification;

class NotificationInitializer : public IInitializer {
public:
    explicit NotificationInitializer(Notification &element);

    StyledBorder &border();

    Nullable<StyledText> &caption();

    StyledText &message();

    Nullable<StyledChar> &icon();

    bool is_wait() const;

    void wait(bool wait);

private:
    Notification &mElement;
};

class Notification : public WriterBase<NotificationInitializer> {
public:
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

    void output_to(std::ostream &outStream) override;

protected:

    void on_write(Buffer &cvs) override;

    NotificationInitializer make_initializer() override;

private:
    StyledBorder mBorder;
    Nullable<StyledChar> mIcon;
    Nullable<StyledText> mCaption;
    StyledText mMessage;
    bool mWait = false;
};



}




