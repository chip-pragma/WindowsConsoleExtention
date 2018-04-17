#pragma once

#include <string>

namespace cpe::ui {

class Scene {
public:
    const std::string &getCaption() const;

    void setCaption(const std::string &caption);

protected:
    std::string mCaption;
};

}
