#pragma once

//
//  ОПРЕДЕЛЕНИЕ ПЛАТФОРМЫ
//

#if defined(__WIN32__) || defined(__MINGW32__)

/// Платформа Windows
#define CPE_PLATFORM_IS_WINDOWS

#include "platform/winapi.h"

#endif