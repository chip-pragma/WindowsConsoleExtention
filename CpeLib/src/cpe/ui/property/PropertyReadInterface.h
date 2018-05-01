#pragma once

namespace cpe {

template<class TValue>
class PropertyReadInterface {

public:

    virtual TValue &operator()() const = 0;

};

}
