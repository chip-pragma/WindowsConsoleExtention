#include "MainVM.h"

#include "../common.h"
#include "../view/CarListView.h"

#include <iostream>
#include <cpe/core/terminal.h>

bool MainVM::onMainMenuReaderResult(cpe::MenuReaderResult &result) {
    if (result.getType() == cpe::ReaderResultType::VALUE) {
        switch (result.getValue()) {
            case MainVM::ID_MM_CARS: {
                CarListVM vmCarList;
                CarListView().showView(vmCarList);
                this->resetView();
                return true;
            }
            case MainVM::ID_MM_EXIT:
                return true;
            default:
                break;
        }
    }

    cpe::StyledText()
        .setFore(cpe::Colors::LT_RED)
        .append("Неверная комадна меню\n"_dos)
        .outputTo(std::cout);
    cpe::term::callPause();
    return false;
}
