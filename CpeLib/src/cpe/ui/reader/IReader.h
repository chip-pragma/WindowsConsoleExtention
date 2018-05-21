#pragma once

namespace cpe {

template <class TResult>
class IReader {
public:
    virtual ~IReader() { };

    virtual void read(TResult &result) = 0;

    virtual void on_read(TResult &result) = 0;
};

}

