#pragma once

#include "cpe/ui/IElementData.h"
#include "cpe/ui/style/TextColor.h"

namespace cpe {

class BaseReaderData : public IElementData {
public:
    ~BaseReaderData() override;

    const TextColor &read_color() const;

    TextColor &read_color();

    const std::string &convert_fail_text() const;

    std::string &convert_fail_text();

protected:
    TextColor mReadStyle;
    std::string mConvertFailText;
};

}




