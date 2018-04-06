#ifndef PROJECT_TEXT_H
#define PROJECT_TEXT_H

#include <string>
#include <vector>

namespace cpe::utils {

class Text {
public:
    /**
     * Удаление начальных и конечных знаков пробелов
     * @param src Обрабатываемая строка
     */
    static void trim(std::string &src);

    /**
     * Деление строки по указанным делителям
     * @param src Исходная делимая строка
     * @param dest Конечный вектор разделенной строки
     * @param anyDelim Последовательность делителей
     */
    static void split(const std::string& src,
                      std::vector<std::string> &dest,
                      const std::string &anyDelim);
};

}


#endif //PROJECT_TEXT_H
