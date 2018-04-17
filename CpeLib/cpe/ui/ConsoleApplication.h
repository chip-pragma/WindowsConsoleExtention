#pragma once

#include <vector>

#include "Scene.h"

namespace cpe::ui {

class ConsoleApplication {
public:
    using SceneList = std::vector<Scene>;

    ConsoleApplication();

    void run(const Scene &beginScene);

    const SceneList &getScenes() const;

private:
    SceneList mScenes;
};

}




