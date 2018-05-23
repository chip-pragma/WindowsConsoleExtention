#include <cpe/core/terminal.h>

#include "TransAgency/view/MainView.h"

int main() {
    MainView mv;
    mv.initialize();
    mv.show(true, false);
    return 0;
}