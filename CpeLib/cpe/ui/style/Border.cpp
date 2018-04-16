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

    _sides.clear();

    _sides[L] = L"\xB3";
    _sides[R] = L"\xB3";
    _sides[T] = L"\xC4";
    _sides[B] = L"\xC4";

    _sides[LT] = L"\xDA";
    _sides[RT] = L"\xBF";
    _sides[LB] = L"\xC0";
    _sides[RB] = L"\xD9";

    _sides[V] = L"\xB3";
    _sides[H] = L"\xC4";

    _sides[VL] = L"\xC3";
    _sides[VR] = L"\xB4";
    _sides[HT] = L"\xC2";
    _sides[HB] = L"\xC1";

    _sides[C] = L"\xC5";

    // Прямые (боковые)
    if (db & Db::LEFT) {
        _sides[L] = L"\xBA";
        _sides[LT] = L"\xD6";
        _sides[LB] = L"\xD3";
        _sides[VL] = L"\xC7";
    }
    if (db & Db::RIGHT) {
        _sides[R] = L"\xBA";
        _sides[RT] = L"\xB7";
        _sides[RB] = L"\xBD";
        _sides[VR] = L"\xB6";
    }
    if (db & Db::TOP) {
        _sides[T] = L"\xCD";
        _sides[LT] = L"\xD5";
        _sides[RT] = L"\xB8";
        _sides[HT] = L"\xD1";
    }
    if (db & Db::BOTTOM) {
        _sides[B] = L"\xCD";
        _sides[LB] = L"\xD4";
        _sides[RB] = L"\xBE";
        _sides[HB] = L"\xCF";
    }

    // Углы
    if ((db & (Db::LEFT | Db::TOP)) == (Db)5)
        _sides[LT] = L"\xC9";
    if ((db & (Db::RIGHT | Db::TOP)) == (Db)5)
        _sides[RT] = L"\xBB";
    if ((db & (Db::LEFT | Db::BOTTOM)) == (Db)5)
        _sides[LB] = L"\xC8";
    if ((db & (Db::RIGHT | Db::BOTTOM)) == (Db)5)
        _sides[RB] = L"\xBC";

    // Прямые (внутренние)
    if (db & Db::IN_V) {
        _sides[V] = L"\xBA";
        _sides[HT] = L"\xD2";
        _sides[HB] = L"\xD0";
        _sides[C] = L"\xD7";
    }
    if (db & Db::IN_H) {
        _sides[H] = L"\xCD";
        _sides[VL] = L"\xC6";
        _sides[VR] = L"\xB5";
        _sides[C] = L"\xD8";
    }

    // Тройник
    if ((db & (Db::IN_V | Db::LEFT)) == (Db)17)
        _sides[VL] = L"\xCC";
    if ((db & (Db::IN_V | Db::RIGHT)) == (Db)18)
        _sides[VR] = L"\xB9";
    if ((db & (Db::IN_H | Db::TOP)) == (Db)36)
        _sides[HT] = L"\xCB";
    if ((db & (Db::IN_H | Db::BOTTOM)) == (Db)40)
        _sides[HB] = L"\xCA";

    // Перекрестье
    if ((db & (Db::IN_H | Db::IN_V)) == (Db)48)
        _sides[C] = L"\xCA";

}

const std::wstring &Border::operator[](const Border::Side &&side) const {
    return _sides[side];
}

}