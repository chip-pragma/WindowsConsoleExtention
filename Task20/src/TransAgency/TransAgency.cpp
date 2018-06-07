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

CarVector TransAgency::getCarList() const {
    CarVector vec;
    for (auto car : mCarList)
        vec.push_back(car);
    return vec;
}

Car &TransAgency::addCar() {
    auto car = new Car();
    mCarList.push_back(car);
    return *car;
}

bool TransAgency::removeCar(Car & car) {
    auto iterFind = std::find(mCarList.begin(), mCarList.end(), &car);
    bool resultFind = (iterFind != mCarList.end());
    if (resultFind)
        mCarList.erase(iterFind);
    return resultFind;
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
        auto &car = this->addCar();
        car.getMark() = "1";
        car.getMaker() = "1";
        car.getSeats() = 1;
        car.getStateNumber() = "1";
    }
    {
        auto &car = this->addCar();
        car.getMark() = "2";
        car.getMaker() = "2";
        car.getSeats() = 2;
        car.getStateNumber() = "2";
    }
    {
        auto &car = this->addCar();
        car.getMark() = "3";
        car.getMaker() = "3";
        car.getSeats() = 3;
        car.getStateNumber() = "3";
    }
    {
        auto &car = this->addCar();
        car.getMark() = "4";
        car.getMaker() = "4";
        car.getSeats() = 4;
        car.getStateNumber() = "4";
    }
}

void TransAgency::onDestroy() {
    for (auto car : mCarList)
        delete car;
}
