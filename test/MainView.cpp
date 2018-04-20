#include "MainView.h"

MainView::MainView(const cpe::ui::ConsoleApp &app) : AView(app) {

}

void MainView::onCreate(std::vector<cpe::ui::IElement> &elements) {
    getController().test();
}