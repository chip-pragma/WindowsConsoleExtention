#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Enums.h"

namespace cpe::tools {

// Определить графические символы рамки
std::map<std::string, std::wstring> define_side_symbols(Flags ds);

// Перекодировать текст
std::string encode(int in, int out, std::string src);

}

