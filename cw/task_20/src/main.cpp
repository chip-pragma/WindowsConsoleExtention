#include <wce/core/console.h>

#include "common.h"
#include "TransAgency.h"
#include "scr/MainScript.h"

using namespace wce;

int main() {
    const char *DATA_FILE_NAME = "trance_agency.data";

    templates::initialize();
    console::setTitle("Транспортное Агенство"_dos);
    
    TransAgency::get().loadData(DATA_FILE_NAME);
    MainScript().run();
    TransAgency::get().saveData(DATA_FILE_NAME);

    return 0;
}