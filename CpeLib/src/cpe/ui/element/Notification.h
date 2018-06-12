#pragma once

#include <string>
#include <optional>

#include "cpe/ui/BaseWriter.h"
#include "cpe/ui/style/BorderStyle.h"
#include "cpe/ui/output/StyledBorder.h"
#include "cpe/ui/output/StyledText.h"
#include "cpe/ui/output/StyledChar.h"
#include "cpe/ui/output/Buffer.h"

namespace cpe {

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




