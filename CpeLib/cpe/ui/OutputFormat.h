#pragma once

#include <string>

namespace cpe::ui {

/**
 * Стиль текста
 */
class OutputFormat {
public:
    OutputFormat();

    /// Возвращает длинну табуляции (в символах)
    uint8_t getTabLength() const;

    /// Задает длину табуляции (в символах)
    void setTabLength(uint8_t tabLength);

    /// Возвращает строку обозначения незаконченного текста
    const std::wstring &getUnfinished() const;

    /// Задает строку обозначения незаконченного текста
    void setUnfinished(const std::wstring &unfinished);

private:
    uint8_t _tabLength;
    std::wstring _unfinished;
};

}
