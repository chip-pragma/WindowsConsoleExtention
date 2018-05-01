#pragma once

#include <cpe/ui/ViewAbstract.h>

#include "controller/MainController.h"

class MainView : public cpe::ViewAbstract<MainController> {
protected:
public:
    explicit MainView(cpe::ControllerAbstract &controller);

protected:
    void initialize();
};


