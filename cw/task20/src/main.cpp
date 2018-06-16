#include <wce/core/console.h>

#include "common.h"
#include "TransAgency.h"
#include "scr/MainScript.h"

int main() {
    using namespace wce;
    const char *DATA_FILE_NAME = "trance_agency.data";

    // TODO styleTemplates

    console::resetColorTable();
    console::setBackground(console::cBlack);
    console::setForeground(console::cWhite);
    console::setTitle("Транспортное Агенство"_dos);
    BorderStyle::finalEncoding = Encoder(Encoder::CP866);

    TransAgency::get().loadData(DATA_FILE_NAME);
    MainScript().run();
    TransAgency::get().saveData(DATA_FILE_NAME);

    return 0;
}