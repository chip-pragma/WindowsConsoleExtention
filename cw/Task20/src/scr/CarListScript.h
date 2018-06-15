#pragma once

#include <wce/ui/BaseScript.h>
#include <wce/ui/element/table/DataTable.h>
#include <wce/ui/element/Label.h>

#include "model/Car.h"

class CarListScript : public wce::BaseScript {
public:
    CarListScript();

    ~CarListScript() override;

protected:
    wce::DataTable<Car> *m_dtCars;

    void onBeforeRunDataTableCar(wce::DataTable<Car> &element);

    void onBeforeRunLabelPageInfo(wce::Label &element);
};


