#include "MainView.h"
#include "common.h"

#include <cpe/ui/element/reader/LineReader.h>

void MainView::initElements() {
    auto &lr1 = addElement<cpe::LineReader>();
    lr1.assignObserver(&MainController::onLineRead);
    lr1.hint("Жопа ("_dos + cpe::LineReader::HINT_PARAM_TEMPLATE + ")"_dos);
    lr1.assignProvider(&MainController::getHintParam);
}


