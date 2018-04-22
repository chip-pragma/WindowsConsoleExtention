#pragma once

#include <string>

namespace cpe {

/**
 *  Базовый класс форматера вывода
 */
class WriterFormat {
public:
    /**
     * Возвращает длинну табуляции (в символах)
     */
    uint8_t getTabLength() const;

    /**
     * Задает длину табуляции (в символах)
     */
    void setTabLength(uint8_t tabLength);

    /**
     * Возвращает строку обозначения незаконченного текста
     */
    const std::string &getUnfinished() const;

    /**
     * Задает строку обозначения незаконченного текста
     */
    void setUnfinished(const std::string &unfinished);

private:
    uint8_t _tabLength = 10;
    std::string _unfinished = "<...>";
};

}
