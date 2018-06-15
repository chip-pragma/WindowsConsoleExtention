#include "IOutputable.h"

namespace wce {

std::ostream &operator<<(std::ostream &os, const IOutputable &outputable) {
    outputable.outputTo(os);
    return os;
}

}