#pragma once

#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

#include <cpe/ui/ControllerInterface.h>


class MainController : public cpe::ControllerInterface {
public:
    void onLineRead(const std::string &value) {
        _mValue = value;
        std::cout << "[onLineRead {value: " << value << "}]" << std::endl;
    }

    const std::string &value() const {
        return _mValue;
    }

    void setHintParam(const std::string &hintParam) {
        _mHintParam = hintParam;
    }

    std::string getHintParam() const {
        std::cout << "[getHintParam {return: " << _mHintParam << "}]" << std::endl;
        return _mHintParam;
    }

private:
    std::string _mValue;
    std::string _mHintParam;
};


