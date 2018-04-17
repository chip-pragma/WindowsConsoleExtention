#include "ConsoleApp.h"

namespace cpe::ui {

ConsoleApp::ConsoleApp()
        : mScenes() {

}

void ConsoleApp::run(const Scene &beginScene) {

}

const ConsoleApp::ViewStack &ConsoleApp::getScenes() const {
    return mScenes;
}


}



