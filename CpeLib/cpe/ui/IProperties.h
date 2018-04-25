#pragma once

#include <functional>


namespace cpe {

//
//  PROTOTYPE
//

class IProperty;

template<class TV>
class AProperty;

template<class TV>
class PropertyRW;

class IProperties;

/////

template<class TV>
using BeforeGetterHandler = void (IProperties::*)();
template<class TV>
using AfterSetterHandler = bool (IProperties::*)(const TV &);

//
//  DECLARATION
//

class IProperty {
    friend class cpe::IProperties;

public:
    virtual ~IProperty() {};

protected:
    IProperty(IProperties *owner);

    IProperties *mOwner;
};

template<class TV>
class AProperty : public IProperty {
    friend class cpe::IProperties;

protected:
    AProperty(IProperties *owner);

    const TV &_get();

    void _set(const TV &value);

    TV mValue;

    BeforeGetterHandler<TV> mGetter = nullptr;
    AfterSetterHandler<TV> mSetter = nullptr;
};

template<class TV>
class PropertyRW : AProperty<TV> {
    friend class cpe::IProperties;

public:

    const TV &get();

    void set(const TV &value);

private:
    PropertyRW(IProperties *owner);
};


class IProperties {
public:
    virtual ~IProperties() {

    };


protected:

    template<class TP>
    void createProperty(TP *&prop);

    template<class TV>
    void assignAfterSetter(AProperty<TV> *prop, AfterSetterHandler<TV> handler);

    template<class TV>
    void assignBeforeGetter(AProperty<TV> *prop, BeforeGetterHandler<TV> handler);

    void destroyProperties();

private:
    std::vector<IProperty *> mPropertyList;
};

//
//  DEFINITION
//

// IProperty //

IProperty::IProperty(IProperties *owner) : mOwner(owner) {

}

// AProperty //

template<class TV>
AProperty<TV>::AProperty(IProperties *owner) : IProperty(owner) {
}

template<class TV>
const TV &AProperty<TV>::_get() {
    if (mGetter != nullptr)
        (mOwner->*mGetter)();
    return mValue;
}

template<class TV>
void AProperty<TV>::_set(const TV &value) {
    if (mValue != value) {
        bool valid = true;
        if (mSetter != nullptr)
            valid = (mOwner->*mSetter)(value);
        if (valid)
            mValue = value;
    }
}

// PropertyRW //

template<class TV>
PropertyRW<TV>::PropertyRW(IProperties *owner) : AProperty<TV>(owner) {
}

template<class TV>
const TV &PropertyRW<TV>::get() {
    return PropertyRW<TV>::_get();
}

template<class TV>
void PropertyRW<TV>::set(const TV &value) {
    PropertyRW<TV>::_set(value);
}

// IProperties //

template<class TP>
void IProperties::createProperty(TP *&prop) {
    static_assert(
            std::is_base_of<IProperty, TP>::value,
            "'ACommand' is not base for template-param 'TC'");

    auto np = new TP(this);
    prop = np;
    mPropertyList.push_back(np);
}

template<class TV>
void IProperties::assignAfterSetter(AProperty<TV> *prop, AfterSetterHandler<TV> handler) {
    prop->mSetter = handler;
}

template<class TV>
void IProperties::assignBeforeGetter(AProperty<TV> *prop, BeforeGetterHandler<TV> handler) {
    prop->mGetter = handler;
};

// TODO =>> ТУТ ТУПАРЫЛАЯ ОШИБКА МУЛЬТИОПРЕДЕЛЕНИЯ <<=
void IProperties::destroyProperties() {
    for (auto prop : mPropertyList)
        delete prop;
}

}
