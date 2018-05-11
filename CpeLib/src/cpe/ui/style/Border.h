#pragma once

#include <string>
#include <map>
#include "DualBorder.h"
#include "cpe/tool/Encoder.h"

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

    std::string operator[](const Side &side) const;

    const Nullable<Encoder> &final_encoding() const;

    Nullable<Encoder> &final_encoding();

    void final_encoding(const Nullable<Encoder> &encTo);

private:
    std::map<Side, std::string> mSides;
    DualBorder mLastApplied;
    Encoder mEncFrom;
    Nullable<Encoder> mEncTo;
};

}
