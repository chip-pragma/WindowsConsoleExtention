#pragma once

#include <cpe/ui/writer/Notification.h>
#include <cpe/ui/view/BaseView.h>

#include "TransAgency/vm/MainVM.h"

class MainView : public cpe::BaseView<MainVM> {
protected:
    void on_initialize() override;

private:
    cpe::Notification mnCaption;
};


