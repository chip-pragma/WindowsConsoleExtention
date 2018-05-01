#pragma once

#include "cpe/ui/property/PropertyProviderAbstract.h"
#include "cpe/ui/property/PropertyObservableAbstract.h"
#include "cpe/ui/ViewInterface.h"
#include "cpe/ui/Buffer.h"

namespace cpe {

class ElementAbstract : public PropertyProviderAbstract,
                        protected PropertyObservableAbstract {
public:
    explicit ElementAbstract(ViewInterface &parent);

    virtual Buffer & run() = 0;

protected:
    Buffer mBuffer;

private:

};

}


