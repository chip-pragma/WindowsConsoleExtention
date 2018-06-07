#include <cpe/core/terminal.h>

#include "TransAgency/TransAgency.h"
#include "common.h"
#include "TransAgency/view/MainView.h"

int main() {
    using namespace cpe;
    const char* DATA_FILE_NAME = "trance_agency.data";

    term::setBackground(cpe::Colors::BLACK);
    term::setForeground(cpe::Colors::WHITE);
    term::setTitle("Транспортное Агенство"_dos);
    BorderStyle::FinalEncoding = Encoder(Encoder::CP866);

    TransAgency::get().loadData(DATA_FILE_NAME);

    MainVM vmMain;
    MainView().showView(vmMain);

    TransAgency::get().saveData(DATA_FILE_NAME);

    term::callPause();
    return 0;
}