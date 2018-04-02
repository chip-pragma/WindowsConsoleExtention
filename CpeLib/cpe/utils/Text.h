#ifndef PROJECT_TEXT_H
#define PROJECT_TEXT_H

#include <string>
#include <vector>

namespace cpe::utils {

class Text {
public:
    // Удаление начальных и конечных знаков пробелов
    static void trim(std::string *src);

    // Деление строки по указанным делителям
    static void split(std::string src,
                      std::vector<std::string> *dest,
                      std::string anyDelim);
};

}


#endif //PROJECT_TEXT_H
