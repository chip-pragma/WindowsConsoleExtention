#include "ConsoleApplication.h"

namespace cpe {

ConsoleApplication::ConsoleApplication(std::ostream &out, std::istream &in) : mOut(out),
                                                                              mIn(in) {
    if (mExist)
        throw Exception("Application context already exists");
    mExist = true;
}

ConsoleApplication::~ConsoleApplication() {
    mExist = false;
}

std::ostream &ConsoleApplication::getOut() {
    return mOut;
}

std::istream &ConsoleApplication::getIn() {
    return mIn;
}

}



