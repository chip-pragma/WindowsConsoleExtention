#include "Border.h"
#include "DualBorder.h"

namespace cpe::ui::style {

Border::Border() = default {
    apply(DualBorder::NONE);
}

Border::Border(const DualBorder &dualBorder) {
    apply(dualBorder);
}

void Border::apply(const DualBorder &db) {
    // Коды рамок:
    /*
    ╔ \xC9	╦ \xCB	╗ \xBB
    ╠ \xCC	╬ \xCE	╣ \xB9	║ \xBA
    ╚ \xC8	╩ \xCA	╝ \xBC
    ═ \xCD

    ┌ \xDA	┬ \xC2	┐ \xBF
    ├ \xC3	┼ \xC5	┤ \xB4	│ - \xB3
    └ \xC0	┴ \xC1	┘ \xD9
    ─ \xC4

    ╓ \xD6	╥ \xD2	╖ \xB7
    ╟ \xC7	╫ \xD7	╢ \xB6
    ╙ \xD3	╨ \xD0	╜ \xBD

    ╒ \xD5	╤ \xD1	╕ \xB8
    ╞ \xC6	╪ \xD8	╡ \xB5
    ╘ \xD4	╧ \xCF	╛ \xBE
    */

    using Db = DualBorder;

    mSides.clear();

    mSides[L] = "\xB3";
    mSides[R] = "\xB3";
    mSides[T] = "\xC4";
    mSides[B] = "\xC4";

    mSides[LT] = "\xDA";
    mSides[RT] = "\xBF";
    mSides[LB] = "\xC0";
    mSides[RB] = "\xD9";

    mSides[V] = "\xB3";
    mSides[H] = "\xC4";

    mSides[VL] = "\xC3";
    mSides[VR] = "\xB4";
    mSides[HT] = "\xC2";
    mSides[HB] = "\xC1";

    mSides[C] = "\xC5";

    // Прямые (боковые)
    if (db & Db::LEFT) {
        mSides[L] = "\xBA";
        mSides[LT] = "\xD6";
        mSides[LB] = "\xD3";
        mSides[VL] = "\xC7";
    }
    if (db & Db::RIGHT) {
        mSides[R] = "\xBA";
        mSides[RT] = "\xB7";
        mSides[RB] = "\xBD";
        mSides[VR] = "\xB6";
    }
    if (db & Db::TOP) {
        mSides[T] = "\xCD";
        mSides[LT] = "\xD5";
        mSides[RT] = "\xB8";
        mSides[HT] = "\xD1";
    }
    if (db & Db::BOTTOM) {
        mSides[B] = "\xCD";
        mSides[LB] = "\xD4";
        mSides[RB] = "\xBE";
        mSides[HB] = "\xCF";
    }

    // Углы
    if ((db & (Db::LEFT | Db::TOP)) == (Db)5)
        mSides[LT] = "\xC9";
    if ((db & (Db::RIGHT | Db::TOP)) == (Db)5)
        mSides[RT] = "\xBB";
    if ((db & (Db::LEFT | Db::BOTTOM)) == (Db)5)
        mSides[LB] = "\xC8";
    if ((db & (Db::RIGHT | Db::BOTTOM)) == (Db)5)
        mSides[RB] = "\xBC";

    // Прямые (внутренние)
    if (db & Db::IN_V) {
        mSides[V] = "\xBA";
        mSides[HT] = "\xD2";
        mSides[HB] = "\xD0";
        mSides[C] = "\xD7";
    }
    if (db & Db::IN_H) {
        mSides[H] = "\xCD";
        mSides[VL] = "\xC6";
        mSides[VR] = "\xB5";
        mSides[C] = "\xD8";
    }

    // Тройник
    if ((db & (Db::IN_V | Db::LEFT)) == (Db)17)
        mSides[VL] = "\xCC";
    if ((db & (Db::IN_V | Db::RIGHT)) == (Db)18)
        mSides[VR] = "\xB9";
    if ((db & (Db::IN_H | Db::TOP)) == (Db)36)
        mSides[HT] = "\xCB";
    if ((db & (Db::IN_H | Db::BOTTOM)) == (Db)40)
        mSides[HB] = "\xCA";

    // Перекрестье
    if ((db & (Db::IN_H | Db::IN_V)) == (Db)48)
        mSides[C] = "\xCA";

}

const std::string &Border::operator[](const Side &&side) const {
    return mSides[side];
}

}