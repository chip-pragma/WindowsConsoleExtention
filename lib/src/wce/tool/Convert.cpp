#include "Convert.h"
#include "text.h"

#include <stdexcept>
#include <utility>
#include <vector>
#include <sstream>
#include <iomanip>

namespace wce::convert {

bool toInt(const std::string &src, int &dest) {
    try {
        dest = std::stoi(src);
    }
    catch (std::invalid_argument &e) {
        return false;
    }
    return true;
}

bool toTime(const std::string &time, bool seconds, time_t &outTime) {
    // Деление на компоненты времени
    std::vector<std::string> strParts;
    text::split(time, strParts, ":");

    // Проверка
    auto nPart = (int) strParts.size();
    if (nPart < 2 || nPart > 3 || (!seconds && nPart > 2))
        return false;

    // Преобразование в int
    std::vector<int> intParts((size_t) nPart);
    for (int i = 0; i < nPart; i++) {
        if (!toInt(strParts[i], intParts[i]) ||
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
    outTime = timeResult;
    return true;
}

bool toDate(const std::string &date, time_t &outDate) {
    // Деление на компоненты времени
    std::vector<std::string> strParts;
    text::split(date, strParts, ".");

    // Проверка
    auto nPart = strParts.size();
    if (nPart != 3)
        return false;

    // Преобразование
    std::istringstream iss(date);
    tm stamp;
    time_t time = std::time(nullptr);
    localtime_s(&stamp, &time);
    stamp.tm_isdst = -1;
    iss >> std::get_time(&stamp, "%d.%m.%Y");
    if (iss.fail())
        return false;

    // Возврат
    outDate = mktime(&stamp);
    return true;
}

std::string fromTime(time_t time, bool seconds) {
    // Преевод в структуру
    std::tm stamp;
    errno_t err = gmtime_s(&stamp, &time);
    if (err)
        throw std::runtime_error("Время не преобразовано");
    stamp.tm_isdst = -1;

    // Формат
    std::string format = "%SH:%M";
    if (seconds) format += ":%S";

    // Преобразование
    char buffer[32];
    std::strftime(buffer, 32, format.c_str(), &stamp);
    return std::string(buffer);
}

std::string fromDate(time_t date) {
    // Преевод в структуру
    std::tm stamp;
    gmtime_s(&stamp, &date);
    stamp.tm_isdst = -1;

    // Преобразование
    char buffer[32];
    std::strftime(buffer, 32, "%d.%m.%Y", &stamp);
    return std::string(buffer);
}

}