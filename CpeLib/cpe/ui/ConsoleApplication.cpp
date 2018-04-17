#include "ConsoleApplication.h"

namespace cpe::ui {

ConsoleApplication::ConsoleApplication()
        : mScenes() {

}

void ConsoleApplication::run(const Scene &beginScene) {

}

const ConsoleApplication::SceneList &ConsoleApplication::getScenes() const {
    return mScenes;
}


}



