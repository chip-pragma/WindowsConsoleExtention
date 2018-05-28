#pragma once

#include <cpe/ui/BaseView.h>
#include <cpe/ui/element/Notification.h>
#include <cpe/ui/element/Label.h>
#include <cpe/ui/element/menu/Menu.h>
#include <cpe/ui/element/menu/MenuItem.h>
#include <cpe/ui/element/menu/MenuSeparator.h>

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
    cpe::MenuReader m_mrMain;
    cpe::MenuItem m_mMain_miCars;
    cpe::MenuItem m_mMain_miClients;
    cpe::MenuItem m_mMain_miRent;
    cpe::MenuItem m_mMain_miExit;
    cpe::MenuSeparator m_mMain_ms1;
    cpe::MenuSeparator m_mMain_ms2;
};


