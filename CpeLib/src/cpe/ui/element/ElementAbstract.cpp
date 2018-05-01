#include "ElementAbstract.h"

namespace cpe {

ElementAbstract::ElementAbstract(ViewInterface &parent) {
    assignObserver(parent);
}

}