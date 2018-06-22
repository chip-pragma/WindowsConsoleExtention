#include "Transport.h"

#include <sstream>

Transport::~Transport() { }

const std::string &Transport::getMark() const {
    return mMark;
}

std::string &Transport::getMark() {
    return mMark;
}

const std::string &Transport::getMaker() const {
    return mMaker;
}

std::string &Transport::getMaker() {
    return mMaker;
}

const uint32_t &Transport::getSeats() const {
    return mSeats;
}

uint32_t &Transport::getSeats() {
    return mSeats;
}

const std::string &Transport::getStateNumber() const {
    return mStateNumber;
}

std::string &Transport::getStateNumber() {
    return mStateNumber;
}

bool Transport::tryGetFieldValue(uint32_t idField, std::string &outField) const {
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

std::string Transport::toString() const {
    std::stringstream ss;
    ss << mMaker << " " << mMark << "(" << mStateNumber << ")";
    return ss.str();
}

void Transport::onSerialize(std::ostream &os) const {

}

void Transport::onDeserialize(std::istream &is) const {

}
