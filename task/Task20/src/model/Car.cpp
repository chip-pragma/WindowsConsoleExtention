#include "Car.h"

#include <sstream>

Car::~Car() { }

const std::string &Car::getMark() const {
    return mMark;
}

std::string &Car::getMark() {
    return mMark;
}

const std::string &Car::getMaker() const {
    return mMaker;
}

std::string &Car::getMaker() {
    return mMaker;
}

const uint32_t &Car::getSeats() const {
    return mSeats;
}

uint32_t &Car::getSeats() {
    return mSeats;
}

const std::string &Car::getStateNumber() const {
    return mStateNumber;
}

std::string &Car::getStateNumber() {
    return mStateNumber;
}

bool Car::tryGetFieldValue(uint32_t idField, std::string &outField) const {
    switch (idField) {
        case FieldIds::ID_FIELD_MARK:
            outField = mMark;
            break;
        case FieldIds::ID_FIELD_MAKER:
            outField = mMaker;
            break;
        case FieldIds::ID_FIELD_STATE_NUMBER:
            outField = mMaker;
            break;
        case FieldIds::ID_FIELD_SEATS:
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

void Car::onSerialize(std::ostream &os) const {

}

void Car::onDeserialize(std::istream &is) const {

}
