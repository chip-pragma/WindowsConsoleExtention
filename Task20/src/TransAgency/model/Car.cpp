#include "Car.h"

#include <sstream>

Car::~Car() { }

const std::string &Car::mark() const {
    return mMark;
}

std::string &Car::mark() {
    return mMark;
}

const std::string &Car::maker() const {
    return mMaker;
}

std::string &Car::maker() {
    return mMaker;
}

const uint32_t &Car::seats() const {
    return mSeats;
}

uint32_t &Car::seats() {
    return mSeats;
}

const std::string &Car::state_number() const {
    return mStateNumber;
}

std::string &Car::state_number() {
    return mStateNumber;
}

bool Car::getFieldValue(uint32_t idField, std::string &outField) const {
    switch (idField) {
        case Fields::F_MARK:
            outField = mMark;
            break;
        case Fields::F_MAKER:
            outField = mMaker;
            break;
        case Fields::F_STATE_NUMBER:
            outField = mMaker;
            break;
        case Fields::F_SEATS:
            outField = std::to_string(mSeats);
            break;
        default:
            return false;
    }
    return true;
}

std::string Car::toString() const {
    std::stringstream ss;
    ss << mMaker << " " << mMark << "(" << mStateNumber << ")";
    return ss.str();
}
