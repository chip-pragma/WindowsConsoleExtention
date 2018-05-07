#include "MainView.h"
#include "common.h"

#include <cpe/ui/reader/LineReader.h>

void MainView::initElements() {
    addElement<cpe::LineReader>()
            .assignObserver(&MainController::onLineRead)
            .setHint("Жопа ("_dos + cpe::LineReader::HINT_VALUE_PARAM + ")"_dos);
}


