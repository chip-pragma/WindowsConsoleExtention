#pragma once

#include <cpe/ui/BaseView.h>
#include <cpe/ui/element/Notification.h>
#include <cpe/ui/element/Label.h>

#include "TransAgency/vm/MainVM.h"

class MainView : public cpe::BaseView<MainVM> {
protected:
    void on_initialize() override;

private:
    cpe::Notification m_nCaption;
    cpe::Label m_lWraps;
};


