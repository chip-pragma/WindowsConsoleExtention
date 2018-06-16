#include "BorderStyle.h"

namespace wce {

std::optional<Encoder> BorderStyle::finalEncoding = std::nullopt;

BorderStyle::BorderStyle() : m_encFrom(Encoder::UTF8) {
    apply(DualBorder::DB_NONE);
}

BorderStyle::BorderStyle(const DualBorder &dualBorder) : m_encFrom(Encoder::UTF8) {
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

    m_lastApplied = static_cast<DualBorder>(db);

    m_sides[SL] = "\u2502";
    m_sides[SR] = "\u2502";
    m_sides[ST] = "\u2500";
    m_sides[SB] = "\u2500";

    m_sides[SLT] = "\u250C";
    m_sides[SRT] = "\u2510";
    m_sides[SLB] = "\u2514";
    m_sides[SRB] = "\u2518";

    m_sides[SV] = "\u2502";
    m_sides[SH] = "\u2500";

    m_sides[SLH] = "\u251C";
    m_sides[SRH] = "\u2524";
    m_sides[STV] = "\u252C";
    m_sides[SBV] = "\u2534";

    m_sides[SC] = "\u253C";

    // Прямые (боковые)
    if ((db & Db::DB_LEFT) != 0) {
        m_sides[SL] = "\u2551";
        m_sides[SLT] = "\u2553";
        m_sides[SLB] = "\u2559";
        m_sides[SLH] = "\u255F";
    }
    if ((db & Db::DB_RIGHT) != 0) {
        m_sides[SR] = "\u2551";
        m_sides[SRT] = "\u2556";
        m_sides[SRB] = "\u255C";
        m_sides[SRH] = "\u2562";
    }
    if ((db & Db::DB_TOP) != 0) {
        m_sides[ST] = "\u2550";
        m_sides[SLT] = "\u2552";
        m_sides[SRT] = "\u2555";
        m_sides[STV] = "\u2564";
    }
    if ((db & Db::DB_BOTTOM) != 0) {
        m_sides[SB] = "\u2550";
        m_sides[SLB] = "\u2558";
        m_sides[SRB] = "\u255B";
        m_sides[SBV] = "\u2567";
    }

    // Углы
    if ((db & (Db::DB_LEFT | Db::DB_TOP)) == 5)
        m_sides[SLT] = "\u2554";
    if ((db & (Db::DB_RIGHT | Db::DB_TOP)) == 6)
        m_sides[SRT] = "\u2557";
    if ((db & (Db::DB_LEFT | Db::DB_BOTTOM)) == 9)
        m_sides[SLB] = "\u255A";
    if ((db & (Db::DB_RIGHT | Db::DB_BOTTOM)) == 10)
        m_sides[SRB] = "\u255D";

    // Прямые (внутренние)
    if ((db & Db::DB_IN_V) != 0) {
        m_sides[SV] = "\u2551";
        m_sides[STV] = "\u2565";
        m_sides[SBV] = "\u2568";
        m_sides[SC] = "\u256B";
    }
    if ((db & Db::DB_IN_H) != 0) {
        m_sides[SH] = "\u2550";
        m_sides[SLH] = "\u255E";
        m_sides[SRH] = "\u2561";
        m_sides[SC] = "\u256A";
    }

    // Тройник
    if ((db & (Db::DB_IN_V | Db::DB_TOP)) == 20)
        m_sides[STV] = "\u2566";
    if ((db & (Db::DB_IN_V | Db::DB_BOTTOM)) == 24)
        m_sides[SBV] = "\u2569";
    if ((db & (Db::DB_IN_H | Db::DB_LEFT)) == 33)
        m_sides[SLH] = "\u2560";
    if ((db & (Db::DB_IN_H | Db::DB_RIGHT)) == 34)
        m_sides[SRH] = "\u2563";

    // Перекрестье
    if ((db & (Db::DB_IN_H | Db::DB_IN_V)) == 48)
        m_sides[SC] = "\u256C";

}

const BorderStyle::DualBorder &BorderStyle::getCurrent() const {
    return m_lastApplied;
}

char BorderStyle::at(const BorderStyle::Side &side) const {
    auto sym = m_sides.at(side);
    if (BorderStyle::finalEncoding.has_value())
        return BorderStyle::finalEncoding->to(m_encFrom.from(sym)).at(0);
    return sym.at(0);
}

char BorderStyle::operator[](const Side &side) const {
    return at(side);
}

}