#include "BorderStyle.h"

namespace wce {

std::optional<Encoder> BorderStyle::FinalEncoding = std::nullopt;

BorderStyle::BorderStyle() : mEncFrom(Encoder::UTF8) {
    apply(DualBorder::DB_NONE);
}

BorderStyle::BorderStyle(const DualBorder &dualBorder) : mEncFrom(Encoder::UTF8) {
    apply(dualBorder);
}

void BorderStyle::apply(int8_t db) {
    // Коды рамок:
    /*
      DOS   UTF-8
    ╔ \xC9  \u2554  ╦ \xCB  \u2566	╗ \xBB  \u2557
    ╠ \xCC  \u2560  ╬ \xCE  \u256C	╣ \xB9  \u2563	║ \xBA  \u2551
    ╚ \xC8	\u255A  ╩ \xCA  \u2569	╝ \xBC  \u255D
    ═ \xCD  \u2550

    ┌ \xDA  \u250C	┬ \xC2  \u252C	┐ \xBF  \u2510
    ├ \xC3  \u251C	┼ \xC5  \u253C	┤ \xB4  \u2524	│ \xB3  \u2502
    └ \xC0  \u2514	┴ \xC1  \u2534	┘ \xD9  \u2518
    ─ \xC4  \u2500

    ╓ \xD6  \u2553	╥ \xD2  \u2565	╖ \xB7  \u2556
    ╟ \xC7  \u255F	╫ \xD7  \u256B	╢ \xB6  \u2562
    ╙ \xD3  \u2559	╨ \xD0  \u2568	╜ \xBD  \u255C

    ╒ \xD5  \u2552	╤ \xD1  \u2564	╕ \xB8  \u2555
    ╞ \xC6  \u255E	╪ \xD8  \u256A	╡ \xB5  \u2561
    ╘ \xD4  \u2558	╧ \xCF  \u2567	╛ \xBE  \u255B
    */

    using Db = DualBorder;

    mLastApplied = static_cast<DualBorder>(db);

    mSides[SL] = "\u2502";
    mSides[SR] = "\u2502";
    mSides[ST] = "\u2500";
    mSides[SB] = "\u2500";

    mSides[SLT] = "\u250C";
    mSides[SRT] = "\u2510";
    mSides[SLB] = "\u2514";
    mSides[SRB] = "\u2518";

    mSides[SV] = "\u2502";
    mSides[SH] = "\u2500";

    mSides[SLH] = "\u251C";
    mSides[SRH] = "\u2524";
    mSides[STV] = "\u252C";
    mSides[SBV] = "\u2534";

    mSides[SC] = "\u253C";

    // Прямые (боковые)
    if ((db & Db::DB_LEFT) != 0) {
        mSides[SL] = "\u2551";
        mSides[SLT] = "\u2553";
        mSides[SLB] = "\u2559";
        mSides[SLH] = "\u255F";
    }
    if ((db & Db::DB_RIGHT) != 0) {
        mSides[SR] = "\u2551";
        mSides[SRT] = "\u2556";
        mSides[SRB] = "\u255C";
        mSides[SRH] = "\u2562";
    }
    if ((db & Db::DB_TOP) != 0) {
        mSides[ST] = "\u2550";
        mSides[SLT] = "\u2552";
        mSides[SRT] = "\u2555";
        mSides[STV] = "\u2564";
    }
    if ((db & Db::DB_BOTTOM) != 0) {
        mSides[SB] = "\u2550";
        mSides[SLB] = "\u2558";
        mSides[SRB] = "\u255B";
        mSides[SBV] = "\u2567";
    }

    // Углы
    if ((db & (Db::DB_LEFT | Db::DB_TOP)) == 5)
        mSides[SLT] = "\u2554";
    if ((db & (Db::DB_RIGHT | Db::DB_TOP)) == 6)
        mSides[SRT] = "\u2557";
    if ((db & (Db::DB_LEFT | Db::DB_BOTTOM)) == 9)
        mSides[SLB] = "\u255A";
    if ((db & (Db::DB_RIGHT | Db::DB_BOTTOM)) == 10)
        mSides[SRB] = "\u255D";

    // Прямые (внутренние)
    if ((db & Db::DB_IN_V) != 0) {
        mSides[SV] = "\u2551";
        mSides[STV] = "\u2565";
        mSides[SBV] = "\u2568";
        mSides[SC] = "\u256B";
    }
    if ((db & Db::DB_IN_H) != 0) {
        mSides[SH] = "\u2550";
        mSides[SLH] = "\u255E";
        mSides[SRH] = "\u2561";
        mSides[SC] = "\u256A";
    }

    // Тройник
    if ((db & (Db::DB_IN_V | Db::DB_TOP)) == 20)
        mSides[STV] = "\u2566";
    if ((db & (Db::DB_IN_V | Db::DB_BOTTOM)) == 24)
        mSides[SBV] = "\u2569";
    if ((db & (Db::DB_IN_H | Db::DB_LEFT)) == 33)
        mSides[SLH] = "\u2560";
    if ((db & (Db::DB_IN_H | Db::DB_RIGHT)) == 34)
        mSides[SRH] = "\u2563";

    // Перекрестье
    if ((db & (Db::DB_IN_H | Db::DB_IN_V)) == 48)
        mSides[SC] = "\u256C";

}

const BorderStyle::DualBorder &BorderStyle::getCurrent() const {
    return mLastApplied;
}

char BorderStyle::at(const BorderStyle::Side &side) const {
    auto sym = mSides.at(side);
    if (BorderStyle::FinalEncoding.has_value())
        return BorderStyle::FinalEncoding->to(mEncFrom.from(sym)).at(0);
    return sym.at(0);
}

char BorderStyle::operator[](const Side &side) const {
    return at(side);
}

}