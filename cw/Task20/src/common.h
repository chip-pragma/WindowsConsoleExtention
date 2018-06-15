#pragma once

#include <wce/tool/Encoder.h>
#include <string>

std::string operator "" _dos(const char *src, size_t size);

std::string fromUtf8ToDos866(const std::string& src);

