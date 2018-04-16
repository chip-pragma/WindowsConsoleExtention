#pragma once

#include <cstdint>

namespace cpe::ui {

class AView {
public:
    virtual ~AView() = 0;

    virtual void layout(uint16_t height) = 0;

    virtual void write(uint16_t nLine) = 0;

protected:

    virtual void resetMap() final;

private:

};


}