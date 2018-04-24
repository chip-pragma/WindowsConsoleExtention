#pragma once

#include <string>

#include "cpe/ui/AProcessor.h"

class TestProcessor : public cpe::AProcessor {
public:
    void preprocess() override;

    void postprocess() override;

    const std::string &getState() const;

private:
    std::string mState;
};


