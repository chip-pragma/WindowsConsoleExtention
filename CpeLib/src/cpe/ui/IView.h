#pragma once

namespace cpe {

class IView {
public:
    virtual ~IView() { };

    virtual void show(bool beforeClean, bool afterClean) = 0;

protected:
    virtual void on_initialize() = 0;

    virtual void on_show_before() = 0;

    virtual void on_show_after() = 0;
};

}




