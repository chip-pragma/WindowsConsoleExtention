#pragma once

#include <string>
#include <vector>

#include "model/Transport.h"

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

class TransAgency {
public:
    TransAgency(const TransAgency &) = delete;

    TransAgency &operator=(const TransAgency &) = delete;

    static TransAgency &get();

    std::vector<Transport>& getCarList();

    void saveData(std::string fileName);

    void loadData(std::string fileName);

protected:
    TransAgency() = default;

    ~TransAgency() = default;

    void onDestroy();

private:
    static TransAgency *mInstance;
    static TransAgencyDestroyer mDestroyer;

    std::vector<Transport> mCarList;
};


