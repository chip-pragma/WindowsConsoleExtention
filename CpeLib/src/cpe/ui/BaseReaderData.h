#pragma once

#include "cpe/ui/BaseElementData.h"
#include "cpe/ui/style/TextColor.h"

namespace cpe {

class BaseReaderData : public BaseElementData {
public:
    ~BaseReaderData() override;

    const TextColor &getReadColor() const;

    TextColor &getColorRead();

    const std::string &getErrorText() const;

    std::string &getErrorText();

protected:
    TextColor mReadStyle;
    std::string mConvertFailText;
};

}




