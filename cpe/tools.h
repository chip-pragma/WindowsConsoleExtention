#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Enums.h"

namespace cpe::tools {

// Удаление начальных и конечных знаков пространства
void trim(std::string* src);
// Деление строки по указанным делителям
void split(std::string src,
		   std::vector<std::string>* dest,
		   std::string anyDelim);

// Строку в int
bool string_to_int(std::string src, int* dest);
// Строку в time_t (время)
bool string_to_time(std::string time, bool seconds, time_t* outTime);
// Строку в time_t (дату)
bool string_to_date(std::string date, time_t* outDate);
// Время (time_t) в строку с указанным форматом
std::string time_to_string(time_t time, bool seconds);
// Дату (time_t) в строку с указанным форматом
std::string date_to_string(time_t date);

// Определить графические символы рамки
std::map<std::string, std::wstring> define_side_symbols(Flags ds);

// Перекодировать текст
std::string encode(int in, int out, std::string src);

}

