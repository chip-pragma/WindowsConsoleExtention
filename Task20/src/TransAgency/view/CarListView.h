#pragma once

#include <cpe/ui/BaseView.h>
#include <cpe/ui/element/Label.h>
#include <cpe/ui/element/table/DataTable.h>
#include <cpe/ui/element/table/DataTableColumn.h>

#include "../vm/CarListVM.h"

class CarListView : public cpe::BaseView<CarListVM> {
    cpe::DataTable m_dtCars;
    cpe::DataTableColumn m_dtCars_dtcMark;
    cpe::DataTableColumn m_dtCars_dtcMaker;
    cpe::DataTableColumn m_dtCars_dtcSeats;
    cpe::DataTableColumn m_dtCars_dtcStateNumber;
public:
    ~CarListView() override;

protected:
    void onInitialize() override;
};


