#include <cpe/tool/Nullable.h>
#include "Border.h"

namespace cpe {

Border::Border() : mEncFrom(Encoder::UTF8) {
    apply(DualBorder::NONE);
}

Border::Border(const DualBorder &dualBorder) : mEncFrom(Encoder::UTF8) {
    apply(dualBorder);
}

void Border::apply(const DualBorder &db) {
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

    // TODO неправильные символы псевдографики

    mLastApplied = db;

    mSides[L] = "\u2502";
    mSides[R] = "\u2502";
    mSides[T] = "\u2500";
    mSides[B] = "\u2500";

    mSides[LT] = "\u250C";
    mSides[RT] = "\u2510";
    mSides[LB] = "\u2514";
    mSides[RB] = "\u2518";

    mSides[V] = "\u2502";
    mSides[H] = "\u2500";

    mSides[VL] = "\u251C";
    mSides[VR] = "\u2524";
    mSides[HT] = "\u252C";
    mSides[HB] = "\u2534";

    mSides[C] = "\u253C";

    // Прямые (боковые)
    if ((db & Db::LEFT) != 0) {
        mSides[L] = "\u2551";
        mSides[LT] = "\u2553";
        mSides[LB] = "\u2559";
        mSides[VL] = "\u255F";
    }
    if ((db & Db::RIGHT) != 0) {
        mSides[R] = "\u2551";
        mSides[RT] = "\u2556";
        mSides[RB] = "\u255C";
        mSides[VR] = "\u2562";
    }
    if ((db & Db::TOP) != 0) {
        mSides[T] = "\u2550";
        mSides[LT] = "\u2552";
        mSides[RT] = "\u2555";
        mSides[HT] = "\u2564";
    }
    if ((db & Db::BOTTOM) != 0) {
        mSides[B] = "\u2550";
        mSides[LB] = "\u2558";
        mSides[RB] = "\u255B";
        mSides[HB] = "\u2567";
    }

    // Углы
    if ((db & (Db::LEFT | Db::TOP)) == 5)
        mSides[LT] = "\u2554";
    if ((db & (Db::RIGHT | Db::TOP)) == 6)
        mSides[RT] = "\u2557";
    if ((db & (Db::LEFT | Db::BOTTOM)) == 9)
        mSides[LB] = "\u255A";
    if ((db & (Db::RIGHT | Db::BOTTOM)) == 10)
        mSides[RB] = "\u255D";

    // Прямые (внутренние)
    if ((db & Db::IN_V) != 0) {
        mSides[V] = "\u2551";
        mSides[HT] = "\u2565";
        mSides[HB] = "\u2568";
        mSides[C] = "\u256B";
    }
    if ((db & Db::IN_H) != 0) {
        mSides[H] = "\u2550";
        mSides[VL] = "\u255E";
        mSides[VR] = "\u2561";
        mSides[C] = "\u256A";
    }

    // Тройник
    if ((db & (Db::IN_V | Db::TOP)) == 20)
        mSides[HT] = "\u2566";
    if ((db & (Db::IN_V | Db::BOTTOM)) == 24)
        mSides[HB] = "\u2569";
    if ((db & (Db::IN_H | Db::LEFT)) == 33)
        mSides[VL] = "\u2560";
    if ((db & (Db::IN_H | Db::RIGHT)) == 34)
        mSides[VR] = "\u2563";

    // Перекрестье
    if ((db & (Db::IN_H | Db::IN_V)) == 48)
        mSides[C] = "\u256C";

}

const DualBorder &Border::last_applied() const {
    return mLastApplied;
}

std::string Border::operator[](const Side &side) const {
    auto sym = mSides.at(side);
    if (mEncTo)
        return mEncTo.get().to(mEncFrom.from(sym));
    return sym;
}

const cpe::Nullable<Encoder> &Border::final_encoding() const {
    return mEncTo;
}

Nullable<Encoder> &Border::final_encoding() {
    return mEncTo;
}

void Border::final_encoding(const cpe::Nullable<Encoder> &encTo) {
    mEncTo.set(encTo);
}

}