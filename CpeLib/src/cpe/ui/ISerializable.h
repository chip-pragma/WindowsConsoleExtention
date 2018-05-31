#pragma once

#include <iostream>

namespace cpe {

class ISerializable {
    friend std::ostream &operator<<(std::ostream &os, const ISerializable &sObj);

    friend std::istream &operator>>(std::istream &is, const ISerializable &desObj);

public:
    virtual ~ISerializable() { }

protected:
    virtual void onSerialize(std::ostream &os) const = 0;

    virtual void onDeserialize(std::istream &is) const = 0;
};

std::ostream &operator<<(std::ostream &os, const ISerializable &sObj);

std::istream &operator>>(std::istream &is, const ISerializable &desObj);

}




