#include "CarListVM.h"

CarListVM::CarListVM() {
    {
        Car car;
        car.getMark() = "1";
        car.getMaker() = "1";
        car.getSeats() = 1;
        car.getStateNumber() = "1";
        mCarList.push_back(car);
    }
    {
        Car car;
        car.getMark() = "2";
        car.getMaker() = "2";
        car.getSeats() = 2;
        car.getStateNumber() = "2";
        mCarList.push_back(car);
    }
    {
        Car car;
        car.getMark() = "3";
        car.getMaker() = "3";
        car.getSeats() = 3;
        car.getStateNumber() = "3";
        mCarList.push_back(car);
    }
    {
        Car car;
        car.getMark() = "4";
        car.getMaker() = "4";
        car.getSeats() = 4;
        car.getStateNumber() = "4";
        mCarList.push_back(car);
    }
}

CarListVM::~CarListVM() { }

void CarListVM::onAfterShow() {
    this->resetView();
}

void CarListVM::onDataTableInit(cpe::DataTableData &data) {
    data.setDataSource(mCarList);
}
