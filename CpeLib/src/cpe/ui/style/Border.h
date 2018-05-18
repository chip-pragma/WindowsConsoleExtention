#pragma once

#include <string>
#include <map>

#include "cpe/tool/Nullable.h"
#include "cpe/tool/Encoder.h"


namespace cpe {

class Border {
public:
    enum DualBorder : uint8_t {
        DB_NONE = 0,
        DB_LEFT = 1,
        DB_RIGHT = 2,
        DB_TOP = 4,
        DB_BOTTOM = 8,
        DB_OUT_V = DB_LEFT | DB_RIGHT,
        DB_OUT_H = DB_TOP | DB_BOTTOM,
        DB_OUT_ALL = DB_OUT_V | DB_OUT_H,
        DB_IN_V = 16,
        DB_IN_H = 32,
        DB_IN_ALL = DB_IN_V | DB_IN_H,
        DB_ALL = DB_OUT_ALL | DB_IN_ALL
    };

    enum Side : uint8_t {
        SL, SR, ST, SB,
        SLT, SRT, SLB, SRB,
        SV, SH,
        SVL, SVR, SHT, SHB,
        SC
    };

    Border();

    explicit Border(const DualBorder &dualBorder);

    void apply(int8_t dualBorder);

    const DualBorder& current() const;

    char at(const Side &side) const;

    char operator[](const Side &side) const;

    const Nullable<Encoder> &final_encoding() const;

    Nullable<Encoder> &final_encoding();

private:
    std::map<Side, std::string> mSides;
    DualBorder mLastApplied = DB_NONE;
    Encoder mEncFrom;
    Nullable<Encoder> mEncTo;
};

}
