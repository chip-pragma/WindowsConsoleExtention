#pragma once

#include <cpe/ui/BaseView.h>
#include <cpe/ui/element/Label.h>
#include <cpe/ui/element/table/DataTable.h>
#include <cpe/ui/element/table/DataTableColumn.h>
#include <cpe/ui/element/menu/Menu.h>
#include <cpe/ui/element/menu/MenuReader.h>
#include <cpe/ui/element/menu/MenuItem.h>
#include <cpe/ui/element/menu/MenuSeparator.h>
#include <cpe/ui/element/Label.h>

#include "../vm/CarListVM.h"

class CarListView : public cpe::BaseView<CarListVM> {
    cpe::DataTable m_dtCars;
    cpe::DataTableColumn m_dtCars_dtcMark;
    cpe::DataTableColumn m_dtCars_dtcMaker;
    cpe::DataTableColumn m_dtCars_dtcSeats;
    cpe::DataTableColumn m_dtCars_dtcStateNumber;
    cpe::Label m_lPageOf;
    cpe::Menu m_mControl;
    cpe::MenuReader m_mrControl;
    cpe::MenuItem m_mControl_miGoToPage;
    cpe::MenuItem m_mControl_miAdd;
    cpe::MenuItem m_mControl_miEdit;
    cpe::MenuItem m_mControl_miRemove;
    cpe::MenuItem m_mControl_miBack;
    cpe::MenuSeparator m_mControl_msSep1;

public:
    ~CarListView() override;

protected:
    void onInitialize() override;
};


