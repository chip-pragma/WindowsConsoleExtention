#pragma once

#include <vector>

#include "AView.h"
#include "IController.h"

namespace cpe::ui {

class ConsoleApp {
public:
    using ViewStack = std::vector<AView<IController>>;

    ConsoleApp();

    void run(const AView &beginScene);

    const ViewStack &getScenes() const;

private:
    ViewStack mScenes;
};

}




