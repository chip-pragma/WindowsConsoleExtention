#pragma once

#include "cpe/ui/BaseWriterData.h"
#include "cpe/ui/BaseWriter.h"

namespace cpe {

class LabelData : public BaseWriterData {
public:
    ~LabelData() override;

    const StyledText &getText() const;

    StyledText &getText();

protected:
    StyledText mText;
};

class Label : public BaseWriter<LabelData> {
public:
protected:
    void onWrite(Buffer &buf) override;
};

}




