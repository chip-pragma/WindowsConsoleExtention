#include "Exception.h"

namespace cpe {

Exception::Exception(const std::string &message) : std::exception(),
                                                   mMessage(message) {

}

const std::string &Exception::message() const {
    return mMessage;
}

}



