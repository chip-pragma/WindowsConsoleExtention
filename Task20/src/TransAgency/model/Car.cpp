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
            return mMark;
        case Fields::F_MAKER:
            return mMaker;
        case Fields::F_STATE_NUMBER:
            return mStateNumber;
        case Fields::F_SEATS:
            return std::to_string(mSeats);
        default:
            return "<?>";
    }
}

std::string Car::toString() const {
    std::stringstream ss;
    ss << mMaker << " " << mMark << "(" << mStateNumber << ")";
    return ss.str();
}
