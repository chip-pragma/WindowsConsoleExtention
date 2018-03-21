#include "tools.h"

#include <ctime>
#include <sstream>
#include <iomanip>
#include <Windows.h>

namespace cpe::tools {
    void trim(std::string *src) {
        auto i = src->begin();
        for (; i != src->end(); i++) {
            char c = *i;
            if (!(c == ' ' || c == '\n' || c == '\t' || c == '\r')) break;
        }
        // Удаление
        src->erase(src->begin(), i);

        auto j = src->rbegin();
        for (; j != src->rend(); j++) {
            char c = *j;
            if (!(c == ' ' || c == '\n' || c == '\t' || c == '\r')) break;
        }
        // Удаление
        src->erase(j.base(), src->rbegin().base());
    }

    void split(std::string src, std::vector<std::string> *dest, std::string anyDelim) {
        if (dest == nullptr)
            throw std::runtime_error("Не указан выходной массив <dest>");
        if (anyDelim.empty())
            return;

        // Подготовка
        std::string line;

        // Деление
        for (auto iSrc = src.begin();
             iSrc != src.end();
             iSrc++) {
            bool separator = false;
            // Сравнение
            for (auto iDelim = anyDelim.begin();
                 iDelim != anyDelim.end();
                 iDelim++) {
                if (*iSrc == *iDelim) {
                    separator = true;
                    break;
                }
            }
            // Получение символа
            if (!separator) {
                line += *iSrc;
            }

            if (separator || iSrc + 1 == src.end()) {
                if (line.size() > 0)
                    dest->push_back(line);
                line.clear();
            }
        }
    }


    bool string_to_int(std::string src, int *dest) {
        try {
            *dest = std::stoi(src);
        }
        catch (std::invalid_argument &e) {
            return false;
        }
        return true;
    }

    bool string_to_time(std::string time, bool seconds, time_t *outTime) {
        // Деление на компоненты времени
        std::vector<std::string> strParts;
        split(time, &strParts, ":");

        // Проверка
        int nPart = strParts.size();
        if (nPart < 2 || nPart > 3 || (!seconds && nPart > 2))
            return false;

        // Преобразование в int
        std::vector<int> intParts(nPart);
        for (int i = 0; i < nPart; i++) {
            if (!string_to_int(strParts[i], &(intParts[i])) ||
                (intParts[i] < 0 || intParts[i] >= 60))
                return false;
        }

        // Формат
        time_t timeResult = 0;
        if (nPart == 2) {
            if (seconds)
                timeResult += intParts[0] * 60 + intParts[1];
            else if (intParts[0] < 24)
                timeResult += intParts[0] * 60 * 60 + intParts[1] * 60;
            else
                return false;
        } else if (nPart == 3) {
            if (intParts[0] < 24)
                timeResult += intParts[0] * 60 * 60 + intParts[1] * 60 + intParts[2];
            else
                return false;
        } else
            return false;

        // Возврат
        *outTime = timeResult;
        return true;
    }

    bool string_to_date(std::string date, time_t *outDate) {
        // Деление на компоненты времени
        std::vector<std::string> strParts;
        split(date, &strParts, ".");

        // Проверка
        auto nPart = strParts.size();
        if (nPart != 3)
            return false;

        // Преобразование
        std::istringstream iss(date);
        tm stamp;
        time_t time = std::time(0);
        localtime_s(&stamp, &time);
        stamp.tm_isdst = -1;
        iss >> std::get_time(&stamp, "%d.%m.%Y");
        if (iss.fail())
            return false;

        // Возврат
        *outDate = mktime(&stamp);
        return true;
    }

    std::string time_to_string(time_t time, bool seconds) {
        // Преевод в структуру
        std::tm stamp;
        errno_t err = gmtime_s(&stamp, &time);
        if (err)
            throw std::runtime_error("Время не преобразовано");
        stamp.tm_isdst = -1;

        // Формат
        std::string format = "%H:%M";
        if (seconds) format += ":%S";

        // Преобразование
        char buffer[32];
        std::strftime(buffer, 32, format.c_str(), &stamp);
        return std::string(buffer);
    }

    std::string date_to_string(time_t date) {
        // Преевод в структуру
        std::tm stamp;
        gmtime_s(&stamp, &date);
        stamp.tm_isdst = -1;

        // Преобразование
        char buffer[32];
        std::strftime(buffer, 32, "%d.%m.%Y", &stamp);
        return std::string(buffer);
    }


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