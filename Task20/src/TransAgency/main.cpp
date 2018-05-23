#include <cpe/core/terminal.h>

#include "TransAgency/view/MainView.h"

int main() {
    MainView mv;
    mv.initialize();
    mv.show(true, false);

    cpe::term::pause();
    return 0;
}