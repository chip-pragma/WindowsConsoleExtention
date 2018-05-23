#pragma once

#include <string>
#include <optional>

#include "cpe/ui/BaseWriter.h"
#include "cpe/ui/BaseWriterData.h"
#include "cpe/ui/style/BorderStyle.h"
#include "cpe/ui/output/StyledBorder.h"
#include "cpe/ui/output/StyledText.h"
#include "cpe/ui/output/StyledChar.h"
#include "cpe/ui/output/Buffer.h"

namespace cpe {

class NotificationData : public BaseWriterData {
public:
    NotificationData();

    const StyledBorder &border() const;

    StyledBorder &border();

    const std::optional<StyledString> &caption() const;

    std::optional<StyledString> &caption();

    const StyledText &text() const;

    StyledText &text();

    const std::optional<StyledChar> &icon() const;

    std::optional<StyledChar> &icon();

    bool is_wait() const;

    void wait(bool wait);

protected:
    StyledBorder mBorder;
    std::optional<StyledChar> mIcon;
    std::optional<StyledString> mCaption;
    StyledText mText;
    bool mWait = false;
};

class Notification : public BaseWriter<NotificationData> {
public:
    ~Notification() override { };

    void output_to(std::ostream &outStream) override;

protected:

    void on_write(Buffer &cvs) override;
};



}




