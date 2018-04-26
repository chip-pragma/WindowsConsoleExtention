#include "AProperties.h"

namespace cpe {

void AProperties::propDestroyAll() {
    for (auto prop : mPropertyList) {
        delete prop;
    }
}

}