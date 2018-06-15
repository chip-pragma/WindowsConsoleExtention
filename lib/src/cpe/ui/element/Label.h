#pragma once

#include "cpe/ui/BaseWriter.h"

namespace cpe {

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




