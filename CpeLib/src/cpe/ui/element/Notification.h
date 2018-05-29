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

    const StyledBorder &getBorder() const;

    StyledBorder &getBorder();

    const std::optional<StyledText> &getCaption() const;

    std::optional<StyledText> &getCaption();

    const StyledText &getText() const;

    StyledText &getText();

    const std::optional<StyledChar> &getIcon() const;

    std::optional<StyledChar> &getIcon();

    bool getWait() const;

    void setWait(bool wait);

protected:
    StyledBorder mBorder;
    std::optional<StyledChar> mIcon;
    std::optional<StyledText> mCaption;
    StyledText mText;
    bool mWait = false;
};

class Notification : public BaseWriter<NotificationData> {
public:
    ~Notification() override { };

    void outputTo(std::ostream &outStream) override;

protected:

    void onWrite(Buffer &cvs) override;
};



}




