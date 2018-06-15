#pragma once

#include <string>
#include <optional>

#include "wce/ui/BaseWriter.h"
#include "wce/ui/style/BorderStyle.h"
#include "wce/ui/output/StyledBorder.h"
#include "wce/ui/output/StyledText.h"
#include "wce/ui/output/StyledChar.h"
#include "wce/ui/output/Buffer.h"

namespace wce {

class Notification : public BaseWriter<Notification> {
public:
    ~Notification() override { };

    const StyledBorder &getBorder() const;

    StyledBorder &getBorderRef();

    const std::optional<StyledText> &getCaption() const;

    std::optional<StyledText> &getCaptionRef();

    const StyledText &getText() const;

    StyledText &getTextRef();

    const std::optional<StyledChar> &getIcon() const;

    std::optional<StyledChar> &getIconRef();

protected:
    StyledBorder mBorder;
    std::optional<StyledChar> mIcon;
    std::optional<StyledText> mCaption;
    StyledText mText;
    bool mWait = false;

    void onWrite(Buffer &cvs) override;
};



}




