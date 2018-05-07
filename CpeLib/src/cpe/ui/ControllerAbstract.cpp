#include "ControllerAbstract.h"

namespace cpe {

ControllerAbstract::ControllerAbstract(ConsoleApplication &app) : mAppContext(app) {

}

ConsoleApplication &ControllerAbstract::getAppContext() {
    return mAppContext;
}

}