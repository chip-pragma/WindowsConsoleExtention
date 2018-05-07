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
#include "ReaderInterface.h"

namespace cpe {

template<class TValue>
class ReaderAbstract : public ReaderInterface {
public:
    using ValueType = TValue;

    template<class TObserver>
    using ValueReadFunc = bool (TObserver::*)(const ValueType &);

    constexpr static const char *HINT_PARAM_TEMPLATE = "%{getReplacedHint}";

protected:
    using PureValueReadFunc = bool (ObserverInterface::*)(const ValueType &);

    Property<std::string> mHint;
    Property<Nullable<Color>> mHintFore;
    Property<Nullable<Color>> mHintBack;
    Property<Nullable<Color>> mInputFore;
    Property<Nullable<Color>> mInputBack;

private:
    PureValueReadFunc mValueReadFunc = nullptr;
};

}




