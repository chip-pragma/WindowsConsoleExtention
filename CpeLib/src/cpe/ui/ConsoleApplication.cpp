#include "ConsoleApplication.h"

namespace cpe {

ConsoleApplication::ConsoleApplication(std::basic_ostream &out, std::basic_istream &in) : mOut(out),
                                                                                          mIn(in) {
    if (mExist)
        throw Exception("Application context already exists");
    mExist = true;
}

ConsoleApplication::~ConsoleApplication() {
    mExist = false;
}

std::basic_ostream &ConsoleApplication::getOut() {
    return mOut;
}

std::basic_istream &ConsoleApplication::getIn() {
    return mIn;
}

}



