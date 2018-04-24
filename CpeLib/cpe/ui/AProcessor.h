#pragma once

namespace cpe {

class AProcessor {
public:
    virtual void preprocess() = 0;

    virtual void postprocess() = 0;
};

}




