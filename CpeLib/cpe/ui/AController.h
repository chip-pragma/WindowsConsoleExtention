#pragma once

namespace cpe {

class AController {
public:
    virtual void preprocess() = 0;

    virtual void postprocess() = 0;
};

}




