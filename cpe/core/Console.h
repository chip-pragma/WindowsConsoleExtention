#ifndef PROJECT_CONSOLE_H
#define PROJECT_CONSOLE_H

#include <string>
#include <Windows.h>

namespace cpe::core::console {

/// Останавливает выполнение до ввода пользователя
void pause();

/// Очищает экран вывода
void clear();

/// Задает текст заголовка окна консоли
void setTitle(const std::string &title);

/// Возвращает текст заголовка окна консоли
std::string getTitle();

/// Задает кодировку для потока ввода
bool setInputCp(uint32_t codePage);

/// Задает кодировку для потока вывода
bool setOutputCp(uint32_t codePage);

/// Возвращает кодировку для потока ввода
uint32_t getInputCp();

/// Возвращает кодировку для потока вывода
uint32_t getOutputCp();

}

#endif //PROJECT_CONSOLE_H
