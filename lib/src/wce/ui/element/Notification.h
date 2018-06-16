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
    StyledBorder border;
    std::optional<StyledChar> icon;
    std::optional<StyledText> caption;
    StyledText text;

    ~Notification() override { };

protected:
    void onWrite(Buffer &cvs) override;
};



}




