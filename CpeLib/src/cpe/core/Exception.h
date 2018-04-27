#pragma once

#include <exception>
#include <string>

namespace cpe {

class Exception : private std::exception {
public:
    Exception() = delete;

    explicit Exception(const std::string &message);

    virtual const std::string &message() const;

protected:
    std::string mMessage;
};

}




