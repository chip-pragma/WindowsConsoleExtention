#pragma once

#include <cpe/ui/BaseScript.h>
#include <cpe/ui/element/table/DataTable.h>
#include <cpe/ui/element/Label.h>

#include "model/Car.h"

class CarListScript : public cpe::BaseScript {
public:
    CarListScript();

    ~CarListScript() override;

protected:
    cpe::DataTable<Car> *m_dtCars;

    void onBeforeRunDataTableCar(cpe::DataTable<Car> &element);

    void onBeforeRunLabelPageInfo(cpe::Label &element);
};


