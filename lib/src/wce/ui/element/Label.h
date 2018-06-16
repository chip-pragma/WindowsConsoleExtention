#pragma once

#include "wce/ui/BaseWriter.h"

namespace wce {

class Label : public BaseWriter<Label> {
public:
    StyledText text;

    ~Label() override;

protected:
    void onWrite(Buffer &buf) override;
};

}




