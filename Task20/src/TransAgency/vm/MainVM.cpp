#include "MainVM.h"

#include "../common.h"
#include "../view/CarListView.h"

#include <iostream>
#include <cpe/core/terminal.h>

bool MainVM::onMainMenuResult(cpe::MenuReaderResult &result) {
    if (result.getType() == cpe::ReaderResultType::VALUE) {
        switch (result.getValue()) {
            case MainVM::ID_MM_CARS: {
                CarListVM vmCarList;
                CarListView().showView(vmCarList);
                return true;
            }
            default:
                break;
        }
    }
    cpe::term::callPause();
    return false;
}
