#pragma once

#include "../Exception.h"
#include "BaseDelegate.h"

namespace wce {

template<class TIns, class TReturn, class ...TParams>
class MemberDelegate : public BaseDelegate<TReturn, TParams...> {
public:
    using InstanceType = TIns;
    using MemberType = TReturn(TIns::*)(TParams...);

    MemberDelegate() = default;

    MemberDelegate(InstanceType &instance, MemberType memFunc);

    ~MemberDelegate() override { }

    TReturn invoke(TParams... params) const override;

    void set(InstanceType &instance, MemberType memFunc);

    void unset();

    bool isSet() const override;

    bool operator==(const BaseDelegate<TReturn, TParams...> &rhs) const override;

private:
    TIns *m_instance = nullptr;
    MemberType m_function = nullptr;
};

template<class TIns, class TReturn, class... TParams>
MemberDelegate<TIns, TReturn, TParams...>::MemberDelegate(InstanceType &instance,
                                                          MemberDelegate::MemberType memFunc) {
    this->set(instance, memFunc);
}

template<class TIns, class TReturn, class... TParams>
TReturn MemberDelegate<TIns, TReturn, TParams...>::invoke(TParams... params) const {
    if (!isSet())
        throw Exception("Delegate is unset");
    return (m_instance->*m_function)(params...);
}

template<class TIns, class TReturn, class... TParams>
void MemberDelegate<TIns, TReturn, TParams...>::set(InstanceType &instance,
                                                    MemberDelegate::MemberType memFunc) {
    m_instance = &instance;
    m_function = memFunc;
}

template<class TIns, class TReturn, class... TParams>
void MemberDelegate<TIns, TReturn, TParams...>::unset() {
    m_instance = nullptr;
    m_function = nullptr;
}

template<class TIns, class TReturn, class... TParams>
bool MemberDelegate<TIns, TReturn, TParams...>::isSet() const {
    return m_instance != nullptr && m_function != nullptr;
}

template<class TIns, class TReturn, class... TParams>
bool MemberDelegate<TIns, TReturn, TParams...>::operator==(const BaseDelegate<TReturn, TParams...> &rhs) const {
    auto casted = dynamic_cast<const MemberDelegate<TIns, TReturn, TParams...>*>(&rhs);
    if (casted != nullptr)
        return m_function == casted->m_function &&
               m_instance == casted->m_instance;
    return false;
}

namespace make {

template <class TIns, class TReturn, class... TParams>
auto delegate(TIns &ins, TReturn(TIns::*func)(TParams...)) {
    return MemberDelegate<TIns, TReturn, TParams...>(ins, func);
};

}

};


