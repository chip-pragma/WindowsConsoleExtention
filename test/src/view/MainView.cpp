#include "MainView.h"
#include "common.h"

#include <cpe/ui/element/reader/LineReader.h>

MainView::MainView(cpe::ControllerAbstract &controller) : ViewAbstract(controller) {
    initialize();
}

void MainView::initialize() {
    auto &es = elements();
    auto &ctrl = controller();
    es.push_back(new cpe::LineReader(
            *this, ctrl.testProperty,
            "Введите текст для теста ридера"_dos));
}


