

#ifndef PROJECT_CONVERTER_H
#define PROJECT_CONVERTER_H

#include <string>
#include <ctime>

namespace cet::utils {

/**
 * Предоставляет методы для преобразования типов
 */
class Converter {
public:
    Converter() = delete;

    // Строку в int
    static bool stringToInt(std::string src, int *dest);

    // Строку в time_t (время)
    static bool stringToTime(std::string time, bool seconds, time_t *outTime);

    // Строку в time_t (дату)
    static bool stringToDate(std::string date, time_t *outDate);

    // Время (time_t) в строку с указанным форматом
    static std::string timeToString(time_t time, bool seconds);

    // Дату (time_t) в строку с указанным форматом
    static std::string dateToString(time_t date);

private:

};

}

#endif //PROJECT_CONVERTER_H
