#include <iostream>
#include <string>
#include "ui/style/Border.h"

namespace {
using cpe::ui::style::Border;
}

void main() {
    Border b;
    auto s = b[b.LB];
}
