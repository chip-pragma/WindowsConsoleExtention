

#ifndef PROJECT_TEXTSTYLE_H
#define PROJECT_TEXTSTYLE_H

#include <string>

namespace cpe::ui::style {

namespace {
class Encoder;
}

/**
 * Стиль текста
 */
class TextFormat {
public:

    TextFormat();

    /// Возвращает длинну табуляции (в символах)
    uint8_t getTabLength() const;

    /// Задает длину табуляции (в символах)
    void setTabLength(uint8_t tabLength);

    /// Возвращает строку обозначения незаконченного текста
    const std::string &getUnfinished() const;

    /// Задает строку обозначения незаконченного текста
    void setUnfinished(const std::string &unfinished);

    Encoder &getInputEncoder() const;

    void setInputEncoder(Encoder &inputEncoder);

    Encoder &getOutputEncoder() const;

    void setOutputEncoder(Encoder &outputEncoder);

private:
    uint8_t _tabLength;
    std::string _unfinished;
    Encoder& _inputEncoder;
    Encoder& _outputEncoder;
};

}


#endif //PROJECT_TEXTSTYLE_H
