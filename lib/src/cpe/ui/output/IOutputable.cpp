#include "IOutputable.h"

namespace cpe {

std::ostream &operator<<(std::ostream &os, const IOutputable &outputable) {
    outputable.outputTo(os);
    return os;
}

}