#include "MainVM.h"

#include "TransAgency/common.h"
#include "../view/CarListView.h"

#include <iostream>
#include <cpe/core/terminal.h>


bool MainVM::onMainMenuResult(cpe::MenuReaderResult &result) {
    if (result.getType() == cpe::ReaderResultType::VALUE) {
        switch (result.getValue()) {
            case MainVM::ID_MM_CARS: {
                // TODO выполнение View через специальные ViewNavigator для возможности отрисовки предыдущего контента
                CarListView carList;
                carList.initialize();
                carList.show(true, false);
                return true;
            }
            default:
                break;
        }
    }
    cpe::term::callPause();
    return false;
}
