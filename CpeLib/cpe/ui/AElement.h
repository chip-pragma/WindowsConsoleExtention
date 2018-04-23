#pragma once

#include "AController.h"
#include "Buffer.h"

namespace cpe {

class AElement {
public:
    // TODO Буфер вывода для каждого элемента
    virtual void run(AController &ctrlr, Buffer &buf) = 0;
};

class ElementList : public std::vector<AElement *> {
public:
    ElementList &operator<<(AElement *elem);
};

ElementList &ElementList::operator<<(AElement *elem) {
    this->push_back(elem);
    return *this;
}

}


