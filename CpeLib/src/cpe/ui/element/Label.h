#pragma once

#include "cpe/ui/BaseWriterData.h"
#include "cpe/ui/BaseWriter.h"

namespace cpe {

class LabelData : public BaseWriterData {
public:
    ~LabelData() override;

    const StyledText &text() const;

    StyledText &text();

protected:
    StyledText mText;
};

class Label : public BaseWriter<LabelData> {
public:
protected:
    void on_write(Buffer &buf) override;
};

}




