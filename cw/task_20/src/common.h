#pragma once

#include <string>

#include <wce/core/console.h>
#include <wce/tool/Encoder.h>
#include <wce/ui/style/BorderStyle.h>
#include <wce/ui/element/Notification.h>
#include <wce/ui/element/menu/Menu.h>
#include <wce/ui/element/menu/MenuReader.h>
#include <wce/ui/element/Label.h>

namespace templates {

void initialize();

wce::Label wrapLabel(uint32_t wrapCount);

wce::Notification infoNotification();

wce::Menu simpleMenu();

wce::MenuReader simpleMenuReader();

}

std::string operator "" _dos(const char *src, size_t size);

std::string fromUtf8ToDos866(const std::string& src);

