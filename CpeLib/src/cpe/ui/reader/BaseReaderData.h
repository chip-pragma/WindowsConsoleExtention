#pragma once

#include "cpe/ui/IData.h"
#include "cpe/ui/style/TextColor.h"

namespace cpe {

class BaseReaderData : public IData {
public:
    ~BaseReaderData() override;

    const TextColor &read_color() const;

    TextColor &read_color();

protected:
    TextColor mReadStyle;
};

}




