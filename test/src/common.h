#pragma once

#include <cpe/utils/Encoder.h>

extern cpe::Encoder<cpe::Encoding::UTF8> encUtf8;
extern cpe::Encoder<cpe::Encoding::CP866> encCp866;

std::string operator "" _dos(const char *src, size_t size);

