#pragma once

#include <string>
#include <vector>

#include <TransAgency/model/Car.h>

class TransAgency;
using TransAgencyDestroyHandler = void(TransAgency::*)();

class TransAgencyDestroyer {
public:
    ~TransAgencyDestroyer();

    void initialize(TransAgency *instance, TransAgencyDestroyHandler destroyHandler);

private:
    TransAgency *mInstance = nullptr;
    TransAgencyDestroyHandler mDestroyHandler = nullptr;
};

using CarVector = std::vector<const Car*>;

class TransAgency {
public:
    TransAgency(const TransAgency &) = delete;

    TransAgency &operator=(const TransAgency &) = delete;

    static TransAgency &get();

    CarVector getCarList() const;

    Car& addCar();

    bool removeCar(Car& car);

    void saveData(std::string fileName);

    void loadData(std::string fileName);

protected:
    TransAgency() = default;

    ~TransAgency() = default;

    void onDestroy();

private:
    static TransAgency *mInstance;
    static TransAgencyDestroyer mDestroyer;

    std::vector<Car*> mCarList;
};


