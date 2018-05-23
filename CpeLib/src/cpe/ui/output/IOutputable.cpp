#include "IOutputable.h"

namespace cpe {

std::ostream &operator<<(std::ostream &os, const IOutputable &outputable) {
    outputable.output_to(os);
    return os;
}

}