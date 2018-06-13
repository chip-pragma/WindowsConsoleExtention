#include <cpe/core/terminal.h>

#include "common.h"
#include "TransAgency.h"
#include "scr/MainScript.h"

int main() {
    using namespace cpe;
    const char* DATA_FILE_NAME = "trance_agency.data";

    term::setBackground(cpe::Colors::BLACK);
    term::setForeground(cpe::Colors::WHITE);
    term::setTitle("Транспортное Агенство"_dos);
    BorderStyle::FinalEncoding = Encoder(Encoder::CP866);

    TransAgency::get().loadData(DATA_FILE_NAME);
    MainScript().run();
    TransAgency::get().saveData(DATA_FILE_NAME);

    return 0;
}