

#ifndef PROJECT_TEXTSTYLE_H
#define PROJECT_TEXTSTYLE_H

#include <string>

namespace cpe::ui::style {

/**
 * Стиль текста
 */
class TextStyle {
public:

    /**
     * Создает стиль текста
     * @param tabLength Длинна табуляции (в символах)
     * @param unfinished Строку обозначения незаконченного текста
     */
    TextStyle(uint8_t tabLength, const std::string &unfinished);

    /**
     * Возвращает длинну табуляции (в символах)
     */
    uint8_t getTabLength() const;

    /**
     * Возвращает строку обозначения незаконченного текста
     */
    const std::string &getUnfinished() const;

private:
    uint8_t _tabLength;
    std::string _unfinished;
};

}


#endif //PROJECT_TEXTSTYLE_H
