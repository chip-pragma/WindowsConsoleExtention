#pragma once

#include <wce/core/console.h>
#include <wce/tool/Encoder.h>
#include <wce/ui/style/BorderStyle.h>
#include <wce/ui/element/Notification.h>

#include <string>

namespace templates {

void initialize();

wce::Notification infoNotification();

}

std::string operator "" _dos(const char *src, size_t size);

std::string fromUtf8ToDos866(const std::string& src);

