#pragma once

#include <cpe/ui/AView.h>

#include "MainController.h"

class MainView : public cpe::ui::AView<MainController> {
public:
    explicit MainView(const cpe::ui::ConsoleApp &app);

protected:
    void onCreate(std::vector<cpe::ui::IElement> &elements) override;
};


