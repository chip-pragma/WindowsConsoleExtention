#pragma once

#include <wce/ui/BaseScript.h>
#include <wce/ui/element/table/DataTable.h>
#include <wce/ui/element/Label.h>

#include "model/Car.h"

class CarListScript : public wce::BaseScript {
public:
    enum : uint32_t {
        ID_MENU_EXIT = 0,
        ID_MENU_ADD,
        ID_MENU_ADD,
    };

    CarListScript();

    ~CarListScript() override;

protected:
    wce::DataTable<Car>* m_dtCars;

    void onBeforeRunDataTableCar(wce::DataTable<Car> &element);

    void onBeforeRunLabelPageInfo(wce::Label &element);
};


