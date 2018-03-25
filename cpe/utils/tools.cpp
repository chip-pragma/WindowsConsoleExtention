#include "tools.h"

#include <ctime>
#include <sstream>
#include <iomanip>
#include <Windows.h>

namespace cpe::tools {

    std::map<std::string, std::wstring> define_side_symbols(Flags ds) {
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

        std::map<std::string, std::wstring> b;
        // Прямые (боковые)
        b.insert(std::pair<std::string, std::wstring>("L", L"\xB3"));
        b.insert(std::pair<std::string, std::wstring>("R", L"\xB3"));
        b.insert(std::pair<std::string, std::wstring>("T", L"\xC4"));
        b.insert(std::pair<std::string, std::wstring>("B", L"\xC4"));
        // Углы
        b.insert(std::pair<std::string, std::wstring>("LT", L"\xDA"));
        b.insert(std::pair<std::string, std::wstring>("RT", L"\xBF"));
        b.insert(std::pair<std::string, std::wstring>("LB", L"\xC0"));
        b.insert(std::pair<std::string, std::wstring>("RB", L"\xD9"));
        // Прямые (внутренние)
        b.insert(std::pair<std::string, std::wstring>("V", L"\xB3"));
        b.insert(std::pair<std::string, std::wstring>("H", L"\xC4"));
        // Тройник
        b.insert(std::pair<std::string, std::wstring>("VL", L"\xC3"));
        b.insert(std::pair<std::string, std::wstring>("VR", L"\xB4"));
        b.insert(std::pair<std::string, std::wstring>("HT", L"\xC2"));
        b.insert(std::pair<std::string, std::wstring>("HB", L"\xC1"));
        // Перекрестье
        b.insert(std::pair<std::string, std::wstring>("+", L"\xC5"));

        // Прямые (боковые)
        if (ds & cpe::DSIDE_LEFT) {
            b["L"] = L"\xBA";
            b["LT"] = L"\xD6";
            b["LB"] = L"\xD3";
            b["VL"] = L"\xC7";
        }
        if (ds & cpe::DSIDE_RIGHT) {
            b["R"] = L"\xBA";
            b["RT"] = L"\xB7";
            b["RB"] = L"\xBD";
            b["VR"] = L"\xB6";
        }
        if (ds & cpe::DSIDE_TOP) {
            b["T"] = L"\xCD";
            b["LT"] = L"\xD5";
            b["RT"] = L"\xB8";
            b["HT"] = L"\xD1";
        }
        if (ds & cpe::DSIDE_BOTTOM) {
            b["B"] = L"\xCD";
            b["LB"] = L"\xD4";
            b["RB"] = L"\xBE";
            b["HB"] = L"\xCF";
        }
        // Углы
        if ((ds & (cpe::DSIDE_LEFT | cpe::DSIDE_TOP)) == 5) {
            b["LT"] = L"\xC9";
        }
        if ((ds & (cpe::DSIDE_RIGHT | cpe::DSIDE_TOP)) == 6) {
            b["RT"] = L"\xBB";
        }
        if ((ds & (cpe::DSIDE_LEFT | cpe::DSIDE_BOTTOM)) == 9) {
            b["LB"] = L"\xC8";
        }
        if ((ds & (cpe::DSIDE_RIGHT | cpe::DSIDE_BOTTOM)) == 10) {
            b["RB"] = L"\xBC";
        }
        // Прямые (внутренние)
        if (ds & cpe::DSIDE_VERTICAL) {
            b["V"] = L"\xBA";
            b["HT"] = L"\xD2";
            b["HB"] = L"\xD0";
            b["+"] = L"\xD7";
        }
        if (ds & cpe::DSIDE_HORIZONTAL) {
            b["H"] = L"\xCD";
            b["VL"] = L"\xC6";
            b["VR"] = L"\xB5";
            b["+"] = L"\xD8";
        }
        // Тройник
        if ((ds & (cpe::DSIDE_VERTICAL | cpe::DSIDE_LEFT)) == 17) {
            b["VL"] = L"\xCC";
        }
        if ((ds & (cpe::DSIDE_VERTICAL | cpe::DSIDE_RIGHT)) == 18) {
            b["VR"] = L"\xB9";
        }
        if ((ds & (cpe::DSIDE_HORIZONTAL | cpe::DSIDE_TOP)) == 36) {
            b["HT"] = L"\xCB";
        }
        if ((ds & (cpe::DSIDE_HORIZONTAL | cpe::DSIDE_BOTTOM)) == 40) {
            b["HB"] = L"\xCA";
        }
        // Перекрестье
        if ((ds & (cpe::DSIDE_VERTICAL | cpe::DSIDE_HORIZONTAL)) == 48) {
            b["+"] = L"\xCE";
        }

        return b;
    }


    std::string encode(int cpIn, int cpOut, std::string src) {


        // Получение кол-ва символов
        int length = MultiByteToWideChar(cpIn, 0, src.c_str(), -1, NULL, 0);
        if (length <= 0)
            return "";
        // Создание wide
        auto srcToWide = new wchar_t[length];
        // В wide
        MultiByteToWideChar(cpIn, 0, src.c_str(), -1, srcToWide, length);

        // Из wide в char
        length = WideCharToMultiByte(cpOut, 0, srcToWide, -1, NULL, 0, NULL, NULL);
        if (length <= 0)
            return "";
        // Создание char
        auto *wideToDest = new char[length];
        // В char
        WideCharToMultiByte(cpOut, 0, srcToWide, -1, wideToDest, length, NULL, NULL);

        // Выходную строку
        std::string result = std::string(wideToDest);

        //очищаем выделенную под переменные память
        delete[]srcToWide;
        delete[]wideToDest;

        return result;
    }

}