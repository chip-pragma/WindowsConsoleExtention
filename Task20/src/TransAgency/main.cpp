#include <cpe/core/terminal.h>

#include "TransAgency/view/MainView.h"

int main() {
    using namespace cpe;

    term::callPause();

    BorderStyle::getFinalEncoding() = Encoder(Encoder::CP866);

    MainView mv;
    mv.initialize();
    mv.show(true, false);

    cpe::term::callPause();
    return 0;
}