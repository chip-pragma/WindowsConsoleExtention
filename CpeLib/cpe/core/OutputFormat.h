#pragma once

#include <string>

namespace cpe::core {

/**
 *  Базовый класс форматера вывода
 */
class OutputFormat {
public:
    OutputFormat();

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

    /**
     * Применяет параметры формата на строку
     * @param src Исходная строка
     * @param maxLength Максимальная длинна. 0 если не задано.
     * @return Новую форматированную строку
     */
    std::string apply(const std::string& src, uint32_t maxLength);

private:
    uint8_t _tabLength;
    std::string _unfinished;
};

}
