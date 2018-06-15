#include "Exception.h"

namespace wce {

Exception::Exception(const std::string &message) : std::exception(),
                                                   mMessage(message) {

}

const char *Exception::what() const noexcept {
    return mMessage.c_str();
}


}



