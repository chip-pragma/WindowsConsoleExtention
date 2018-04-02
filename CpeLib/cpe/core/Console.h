#pragma once

#include <string>

#include "Point.h"

namespace cpe::core::console {

/**
 * Останавливает выполнение до ввода пользователя
 */
void pause();

/**
 * Очищает экран вывода
 */
void clear();

/**
 * Задает текст заголовка окна консоли
 */
void setTitle(const std::string &title);

/**
 * Возвращает текст заголовка окна консоли
 */
std::string getTitle();

/**
 * Задает кодировку для потока ввода
 * @return результат применения новой кодировки
 */
bool setInputCp(uint32_t codePage);

/**
 * Задает кодировку для потока вывода
 * @return результат применения новой кодировки
 */
bool setOutputCp(uint32_t codePage);

/**
 * Возвращает кодировку для потока ввода
 */
uint32_t getInputCp();

/**
 * Возвращает кодировку для потока вывода
 */
uint32_t getOutputCp();

/**
 * Задает размер (в символах) буфера окна консоли
 * @return результат применения размера
 */
bool setBufferSize(const Point &size);

/**
 * Возвращает размер (в символах) буфера окна консоли
 */
Point getBufferSize();

/**
 * Задает позицию символьного курсора консоли
 * @return результат применения позиции
 */
bool setCursorPosition(const Point &pos);

/**
 * Возвращает позицию символьного курсора консоли
 */
Point getCursorPosition();

}
