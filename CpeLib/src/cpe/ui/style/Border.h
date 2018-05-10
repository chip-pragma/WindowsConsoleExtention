#pragma once

#include <string>
#include <map>
#include "DualBorder.h"

namespace cpe {

class Border {
public:
    enum Side : int {
        L, R, T, B,
        LT, RT, LB, RB,
        V, H,
        VL, VR, HT, HB,
        C
    };

    Border();

    explicit Border(const DualBorder &dualBorder);

    void apply(const DualBorder &dualBorder);

    const DualBorder& last_applied() const;

    const std::string &operator[](const Side &side) const;

private:
    std::map<Side, std::string> mSides;
    DualBorder mLastApplied;
};

}
