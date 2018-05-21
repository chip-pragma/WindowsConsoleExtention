#pragma once

#include "ICuiElement.h"

namespace cpe {

template<class TData>
class BaseCuiElement : ICuiElement {
public:
    template<class TController>
    using DataReceiverFunc = void (TController::*)(TData &);

    BaseCuiElement();

    ~BaseCuiElement() override;

    virtual const TData &data() const;

    virtual TData &data();

    template<class TController>
    void bind_data(DataReceiverFunc<TController> func);

    void fire_data(IController &ctrl);

protected:
    using _PureDataReceiverFunc = void (IController::*)(TData &);

    TData* mData;
    _PureDataReceiverFunc mDataReceiverFunc = nullptr;
};

template<class TData>
BaseCuiElement<TData>::BaseCuiElement() {
    mData = new TData();
}

template<class TData>
BaseCuiElement<TData>::~BaseCuiElement() {
    delete mData;
}

template<class TData>
const TData &BaseCuiElement<TData>::data() const {
    return *mData;
}

template<class TData>
TData &BaseCuiElement<TData>::data() {
    return *mData;
}

template<class TData>
template<class TController>
void BaseCuiElement<TData>::bind_data(DataReceiverFunc<TController> func) {
    mDataReceiverFunc = static_cast<_PureDataReceiverFunc>(func);
}

template<class TData>
void BaseCuiElement<TData>::fire_data(IController &ctrl) {
    if (mDataReceiverFunc)
        (ctrl.*mDataReceiverFunc)(*mData);
}

}




