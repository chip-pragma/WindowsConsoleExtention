#include "Scene.h"

namespace cpe::ui {


const std::string &Scene::getCaption() const {
    return mCaption;
}

void Scene::setCaption(const std::string &caption) {
    mCaption = caption;
}
}