#pragma once

#include <exception>
#include <string>

namespace cpe {

class Exception : private std::exception {
public:
    explicit Exception(const std::string &message);

private:
    const char *what() const noexcept override;

protected:
    std::string mMessage;
};

}




