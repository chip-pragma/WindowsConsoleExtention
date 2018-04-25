#include "AProperties.h"

namespace cpe {

void AProperties::destroyProperties() {
    for (auto prop : mPropertyList)
        delete prop;
}

}





