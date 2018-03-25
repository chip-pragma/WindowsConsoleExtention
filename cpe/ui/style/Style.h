#ifndef PROJECT_STYLE_H
#define PROJECT_STYLE_H

#include <string>
#include <map>

namespace cpe::ui {

/**
 * Вспомогательный тип размером в 1 байт для использования как набора флагов
 */
typedef unsigned char FlagsByte;

class Style {
public:
    // Определить графические символы рамки
    std::map<std::string, std::wstring> define_side_symbols(FlagsByte ds);
};

}

#endif //PROJECT_STYLE_H
