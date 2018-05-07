#pragma once

#include <iostream>

#include "cpe/core/terminal.h"
#include "cpe/core/Point.h"
#include "cpe/core/Color.h"
#include "cpe/tool/text.h"
#include "cpe/tool/property/ObserverInterface.h"
#include "cpe/tool/property/ProviderInterface.h"
#include "cpe/tool/property/Property.h"
#include "cpe/tool/property/Nullable.h"
#include "cpe/tool/property/PropertyManagerAbstract.h"
#include "cpe/ui/style/TextCharStyle.h"
#include "ReaderInterface.h"

namespace cpe {

template<class TValue>
class ReaderAbstract : public ReaderInterface,
                       public PropertyManagerAbstract {
public:
    using ValueType = TValue;

    Property<ValueType> value;
    Property<TextCharStyle> readStyle;

protected:
};

}




