#pragma once

#include <cpe/ui/BaseView.h>
#include <cpe/ui/element/Notification.h>
#include <cpe/ui/element/Label.h>
#include <cpe/ui/element/menu/Menu.h>
#include <cpe/ui/element/menu/NumericMenuItem.h>

#include "TransAgency/vm/MainVM.h"

class MainView : public cpe::BaseView<MainVM> {
protected:
public:
    MainView();

    ~MainView() override;

protected:

    void on_initialize() override;

private:
    cpe::Notification m_nCaption;
    cpe::Label m_lWraps;
    cpe::Menu m_mMain;
    cpe::NumericMenuItem m_mMain_nmiCars;
    cpe::NumericMenuItem m_mMain_nmiClients;
    cpe::NumericMenuItem m_mMain_nmiRent;
    cpe::NumericMenuItem m_mMain_nmiExit;
};


