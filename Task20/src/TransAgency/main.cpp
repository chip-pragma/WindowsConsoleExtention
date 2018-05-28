#include <cpe/core/terminal.h>

#include "TransAgency/view/MainView.h"

int main() {
    using namespace cpe;

    term::pause();

    BorderStyle::final_encoding() = Encoder(Encoder::CP866);

    MainView mv;
    mv.initialize();
    mv.show(true, false);

    cpe::term::pause();
    return 0;
}