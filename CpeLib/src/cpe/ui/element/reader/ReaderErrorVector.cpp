#include "ReaderErrorVector.h"

namespace cpe {

void ReaderErrorVector::output() const {
    for (const auto& err : *this)
        std::cout << err << "\n";
    std::cout.flush();
}
}



