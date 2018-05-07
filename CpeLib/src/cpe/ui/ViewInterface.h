#pragma once

namespace cpe {

class ViewInterface {
public:
    virtual void run(bool beforeClear, bool afterClear) = 0;
};

}