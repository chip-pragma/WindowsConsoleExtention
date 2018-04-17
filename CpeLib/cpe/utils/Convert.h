#pragma once

#include <string>
#include <ctime>

namespace cpe::utils::convert {

// Строку в int
bool toInt(const std::string &src, int &dest);

// Строку в time_t (время)
bool toTime(const std::string &time, bool seconds, time_t &outTime);

// Строку в time_t (дату)
bool toDate(const std::string &date, time_t &outDate);

// Время (time_t) в строку с указанным форматом
std::string fromTime(time_t time, bool seconds);

// Дату (time_t) в строку с указанным форматом
std::string fromDate(time_t date);

}
