#pragma once

#include "wce/ui/BaseWriter.h"

namespace wce {

class Label : public BaseWriter<Label> {
public:
    ~Label() override;

    const StyledText &getText() const;

    StyledText &getTextRef();

protected:
    StyledText mText;

    void onWrite(Buffer &buf) override;
};

}




