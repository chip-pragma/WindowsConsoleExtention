#include "CarListVM.h"

#include <TransAgency/TransAgency.h>

#include <functional>
#include <sstream>


CarListVM::CarListVM()
    : mTableModel(TransAgency::get().getCarList()) {

}

CarListVM::~CarListVM() { }

void CarListVM::onDataTableInit(cpe::DataTableData<Car> &data) {
    data.setDataSource(mTableModel.apply());
}

void CarListVM::onLabelPageInit(cpe::LabelData &data) {
    std::stringstream ss;
    ss << "[Страница "
       << mTableModel.getPageNumber() + 1
       << " из "
       << mTableModel.getPageCount()
       << "]\n";
    data.getText().clear().append(fromUtf8ToDos866(ss.str()));
}
