#pragma once

#include <cstdint>

namespace cpe::core {

/**
 * Цвета, доступные в консоли
 */
class Color {
public:
    static const Color BLACK;
    static const Color BLUE;
    static const Color GREEN;
    static const Color TEAL;
    static const Color RED;
    static const Color PURPLE;
    static const Color YELLOW;
    static const Color GRAY;
    static const Color WHITE;
    static const Color LT_BLUE;
    static const Color LT_GREEN;
    static const Color LT_TEAL;
    static const Color LT_RED;
    static const Color LT_PURPLE;
    static const Color LT_YELLOW;
    static const Color LT_GRAY;

    Color();

    Color(uint8_t r, uint8_t g, uint8_t b);

    /**
     * Возвращает красный компонент цвета
     */
    uint8_t getR() const;

    /**
     * Задает красный компонент цвета
     */
    void setR(uint8_t r);

    /**
     * Возвращает зеленый компонент цвета
     */
    uint8_t getG() const;

    /**
     * Задает зеленый компонент цвета
     */
    void setG(uint8_t g);

    /**
     * Возвращает синий компонент цвета
     */
    uint8_t getB() const;

    /**
     * Задает синий компонент цвета
     */
    void setB(uint8_t b);

    /**
     * Задает все компоненты цвета
     */
    void setAll(uint8_t r, uint8_t g, uint8_t b);

    /**
     * Яркий цвет? (Один или несколько из компонентов цвета больше 127)
     */
    bool isIntensive() const;

private:
    uint8_t _r;
    uint8_t _g;
    uint8_t _b;
};

}

