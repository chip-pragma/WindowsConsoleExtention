#include "TransAgency.h"

#include <algorithm>

TransAgencyDestroyer::~TransAgencyDestroyer() {
    (mInstance->*mDestroyHandler)();
}

void TransAgencyDestroyer::initialize(TransAgency *instance, TransAgencyDestroyHandler destroyHandler) {
    mInstance = instance;
    mDestroyHandler = destroyHandler;
}

TransAgency *TransAgency::mInstance = nullptr;
TransAgencyDestroyer TransAgency::mDestroyer;

std::vector<Car>& TransAgency::getCarList() {
    return mCarList;
}

TransAgency &TransAgency::get() {
    if (!mInstance) {
        mInstance = new TransAgency();
        mDestroyer.initialize(mInstance, &TransAgency::onDestroy);
    }
    return *mInstance;
}

void TransAgency::saveData(std::string fileName) {

}

void TransAgency::loadData(std::string fileName) {
    {
        Car car;
        car.getMark() = "2";
        car.getMaker() = "2";
        car.getSeats() = 2;
        car.getStateNumber() = "2";
        getCarList().push_back(car);
    }
    {
        Car car;
        car.getMark() = "1";
        car.getMaker() = "1";
        car.getSeats() = 1;
        car.getStateNumber() = "1";
        getCarList().push_back(car);
    }
    {
        Car car;
        car.getMark() = "4";
        car.getMaker() = "4";
        car.getSeats() = 4;
        car.getStateNumber() = "4";
        getCarList().push_back(car);
    }
    {
        Car car;
        car.getMark() = "3";
        car.getMaker() = "3";
        car.getSeats() = 3;
        car.getStateNumber() = "3";
        getCarList().push_back(car);
    }
}

void TransAgency::onDestroy() {

}
