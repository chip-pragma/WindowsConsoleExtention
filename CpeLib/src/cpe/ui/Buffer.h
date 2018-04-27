#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

#include "cpe/core/Color.h"
#include "cpe/core/Point.h"
#include "cpe/core/Terminal.h"
#include "WriterFormat.h"

namespace cpe {

/**
 * Буффер специальных символов для последующего вывода в стандартный поток вывода
 */
class Buffer {
public:

    Buffer();

    ~Buffer();

    /**
     * Режим назначения цвета. True для фона, false для текста.
     */
    bool isColorSetBg() const;

    /**
     * Задает режим назначения цвета
     * @param colorSetMode True для фона, false для текста.
     */
    void setColorSetBg(bool colorSetMode);

    /**
     * Возвращает цвет заданного режима, если используется
     * @param color <i>[out]<i/> Ссылка для возврата используемого цвета
     * @return true, если цвет используется и возвращен. Иначе false.
     */
    bool getColor(cpe::Color &color) const;

    /**
     * Назначает цвет заданного режима
     */
    void setColor(const cpe::Color &color);

    /**
     * Отключить использование цвета заданного режима
     */
    void unsetColor();

    /**
     * Возвращает максимальную ширину буфера, если назначена
     * @param width <i>[out]<i/> Ссылка для возврата ширины
     * @return  true, если ширина назначена и возвращена. Иначе false.
     */
    bool getWidth(int &width) const;

    /**
     * Задает максимальную ширину буфера
     */
    void setWidth(int width);

    /**
     * Отключает использование максимальной ширины
     */
    void unsetWidth();

    /**
     * Возвращает максимальную высоту буфера, если назначена
     * @param width <i>[out]<i/> Ссылка для возврата высоты
     * @return  true, если высоту назначена и возвращена. Иначе false.
     */
    bool getHeight(int &height) const;

    /**
     * Задает максимальную высоту буфера
     */
    void setHeight(int height);

    /**
     * Отключает использование максимальной высоту
     */
    void unsetHeight();

    /**
     * Возвращает форматер вывода
     */
    const WriterFormat &getFormat() const;

    /**
     * Задает форматер вывода
     */
    void setFormat(const WriterFormat &format);

    /**
     * Добавляет в буфер строку
     * @return *this
     */
    Buffer &pushBack(const std::string &str);

    /**
     * Добавляет в буфер подбуфер. Если добавляется этот же буфер, то функция ничего не выполняет.
     * @return *this
     */
    Buffer &pushBack(const Buffer &buffer);

    /**
     * Выводит все содержимое буфера в стандартный поток вывода
     */
    void flush();

    /**
     * Удаляет заданное кол-во последних символов буфера
     * @param count Кол-во удаляемых символов
     */
    void popBack(uint64_t count);

    /**
     * Очищает буфер
     */
    void clear();

    /**
     * Аналогично pushBack
     */
    Buffer &operator<<(const std::string &str);

    /**
     * Применяет манипулятор буфера
     */
    Buffer &operator<<(Buffer &(*manip)(Buffer &));

    /**
     * Аналогично pushBack
     */
    Buffer &operator<<(const Buffer &buf);

private:
    /**
     * Обертка цвета с флагом использования
     */
    struct _Color {
        Color mColor;
        bool mUsing = false;
    };

    /**
     * Стилизованный символ с заданным цветом фона и текста
     */
    struct _StyledChar {
        _StyledChar() {

        }

        _StyledChar(const _Color &fore,
                    const _Color &back,
                    char aChar) : mFore(fore),
                                  mBack(back),
                                  mChar(aChar) {}

        _Color mFore;
        _Color mBack;
        char mChar = ' ';
    };

    /**
     * Специальный сивол буфера
     */
    struct _Symbol {
        enum : int {
            UNDEFINED,
            BUFFER_POINTER,
            STYLED_CHAR
        };

        _Symbol() {

        }

        explicit _Symbol(const Buffer *buffer) : mBuffer(buffer),
                                                 mType(BUFFER_POINTER) {}

        explicit _Symbol(const _StyledChar &styledChar) : mSChar(styledChar),
                                                          mType(STYLED_CHAR) {}

        int mType = UNDEFINED;
        union {
            const Buffer *mBuffer = nullptr;
            _StyledChar mSChar;
        };
    };

    /**
     * Обертка числового значения с флагом использования
     */
    struct _Maximum {
        int mValue = 0;
        bool mUsing = false;

        _Maximum() {

        }

        explicit _Maximum(int val) : mValue(val) {
            mUsing = true;
        }
    };

    // Символы буфера
    std::vector<_Symbol> mSymbols;
    // Режим применения цвета
    bool mColorSetBg = false;
    // Цвет текста
    _Color mFore;
    // Увет фона
    _Color mBack;
    // Ширина
    _Maximum mWidth;
    // Высота
    _Maximum mHeight;
    // Форматер вывода
    WriterFormat mFormat;

    // Раскрывает все подбуферы, указанные в данном буфере
    Point _simplify(std::vector<_StyledChar> &chars,
                    Point outerPos,
                    const _Maximum &outerMaxWidth,
                    const _Maximum &outerMaxHeight) const;

    // Пробует добавить строку учитывая заданные максимальные ширину и высоту, если заданы
    inline bool
    _tryAddLine(Point &local,
                const Point &outer,
                const _Maximum &maxWidth,
                const _Maximum &maxHeight,
                std::vector<_StyledChar> &chars) const;
};

}




