#include "TransAgency.h"

#include <algorithm>

#include "common.h"

TransAgencyDestroyer::~TransAgencyDestroyer() {
    (mInstance->*mDestroyHandler)();
}

void TransAgencyDestroyer::initialize(TransAgency *instance, TransAgencyDestroyHandler destroyHandler) {
    mInstance = instance;
    mDestroyHandler = destroyHandler;
}

TransAgency *TransAgency::mInstance = nullptr;
TransAgencyDestroyer TransAgency::mDestroyer;

std::vector<Transport>& TransAgency::getCarList() {
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
        Transport car;
        car.getMark() = "Рено"_dos;
        car.getMaker() = "2";
        car.getSeats() = 2;
        car.getStateNumber() = "2";
        getCarList().push_back(car);
    }
    {
        Transport car;
        car.getMark() = "Пежо"_dos;
        car.getMaker() = "1";
        car.getSeats() = 1;
        car.getStateNumber() = "1";
        getCarList().push_back(car);
    }
    {
        Transport car;
        car.getMark() = "Ягуар"_dos;
        car.getMaker() = "5";
        car.getSeats() = 5;
        car.getStateNumber() = "5";
        getCarList().push_back(car);
    }
    {
        Transport car;
        car.getMark() = "Лексус"_dos;
        car.getMaker() = "4";
        car.getSeats() = 4;
        car.getStateNumber() = "4";
        getCarList().push_back(car);
    }
    {
        Transport car;
        car.getMark() = "Вольво"_dos;
        car.getMaker() = "3";
        car.getSeats() = 3;
        car.getStateNumber() = "3";
        getCarList().push_back(car);
    }
}

void TransAgency::onDestroy() {

}
