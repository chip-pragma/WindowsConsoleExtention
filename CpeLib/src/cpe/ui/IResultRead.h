#pragma once

namespace cpe {

class IResultRead {
public:
    IResultRead() { }

    virtual ~IResultRead() { }

    virtual bool is_valid() const = 0;

    virtual void valid(bool value) = 0;
};

}
