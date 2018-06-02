#include <cpe/core/terminal.h>

#include "TransAgency/view/MainView.h"

int main() {
    using namespace cpe;

    cpe::term::setTitle("Транспортное Агенство");
    BorderStyle::FinalEncoding = Encoder(Encoder::CP866);

    MainVM vmMain;
    MainView().showView(vmMain);

    term::callPause();
    return 0;
}