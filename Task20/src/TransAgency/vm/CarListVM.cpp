#include "CarListVM.h"

#include <TransAgency/TransAgency.h>

CarListVM::CarListVM() {

}

CarListVM::~CarListVM() { }

void CarListVM::onDataTableInit(cpe::DataTableData &data) {
    data.setDataSource(TransAgency::get().getCarList());
}
