#pragma once

#include <string>
#include <map>
#include <optional>

#include "wce/tool/Encoder.h"


namespace wce {

class BorderStyle {
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
        SLH, SRH, STV, SBV,
        SC
    };

    static std::optional<Encoder> finalEncoding;

    BorderStyle();

    explicit BorderStyle(const DualBorder &dualBorder);

    void apply(int8_t dualBorder);

    const DualBorder& getCurrent() const;

    char at(const Side &side) const;

    char operator[](const Side &side) const;

private:
    std::map<Side, std::string> m_sides;
    DualBorder m_lastApplied = DB_NONE;
    Encoder m_encFrom;
};

}
