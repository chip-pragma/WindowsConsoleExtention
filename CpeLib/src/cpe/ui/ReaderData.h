#pragma once

#include <algorithm>
#include <vector>

#include "cpe/ui/BaseReaderData.h"
#include "cpe/ui/IValidator.h"

namespace cpe {

template<class TValue>
class ReaderData : public BaseReaderData {
public:
    template<class TValidator>
    void addValidator(const TValidator &validator);

    template<class TValidator>
    void removeValidator(const TValidator &validator);

    std::vector<std::string> validate(const TValue &value) const;

protected:
    std::vector<IValidator<TValue> *> mValidators;
};

template<class TValue>
template<class TValidator>
void ReaderData<TValue>::addValidator(const TValidator &validator) {
    mValidators.push_back(static_cast<IValidator<TValue> *>(new TValidator(validator)));
}

template<class TValue>
template<class TValidator>
void ReaderData<TValue>::removeValidator(const TValidator &validator) {
    auto finded = std::find(
            mValidators.cbegin(), mValidators.cend(),
            static_cast<const IValidator<TValue> *>(&validator));
    if (finded != mValidators.cend())
        mValidators.erase(finded);
}

template<class TValue>
std::vector<std::string> ReaderData<TValue>::validate(const TValue &value) const {
    std::vector<std::string> errorList;
    for (const IValidator<TValue> *valid : mValidators)
        valid->validate(value, errorList);
    return errorList;
}

}




