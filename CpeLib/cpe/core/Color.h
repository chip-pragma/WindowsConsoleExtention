#pragma once

#include <cstdint>

namespace cpe::core {

/**
 * Цвета, доступные в консоли
 */
class Color {
public:
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

