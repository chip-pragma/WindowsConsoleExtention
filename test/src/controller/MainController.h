#pragma once

#include <string>
#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

#include <cpe/core/terminal.h>
#include <cpe/ui/ControllerInterface.h>

#include "common.h"

class MainController : public cpe::ControllerInterface {
public:
    bool onLineRead(const std::string &value) {
        _mValue = value;
        bool valid = (value == "yes");
        if (!valid) {
            std::cout << "НЕ тО! ЕптА"_dos << std::endl;
            cpe::term::pause();
        }
        return valid;

        // TODO вызывать "модальное View", если валидация не прошла.
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


