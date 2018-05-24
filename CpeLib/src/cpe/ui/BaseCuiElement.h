#pragma once

#include "ICuiElement.h"

namespace cpe {

template<class TData>
class BaseCuiElement : public ICuiElement {
public:
    template<class TViewModel>
    using DataReceiverFunc = void (TViewModel::*)(TData &);

    BaseCuiElement();

    ~BaseCuiElement() override;

    virtual const TData &data() const;

    virtual TData &data();

    template<class TViewModel>
    void bind_data(DataReceiverFunc<TViewModel> func);

    void fire_data(IViewModel &ctrl);

protected:
    using _PureDataReceiverFunc = void (IViewModel::*)(TData &);

    TData *mData;
    _PureDataReceiverFunc mDataReceiverFunc = nullptr;

    void on_before_run() override { };

    void on_after_run() override { };
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
template<class TViewModel>
void BaseCuiElement<TData>::bind_data(DataReceiverFunc<TViewModel> func) {
    mDataReceiverFunc = static_cast<_PureDataReceiverFunc>(func);
}

template<class TData>
void BaseCuiElement<TData>::fire_data(IViewModel &ctrl) {
    if (mDataReceiverFunc)
        (ctrl.*mDataReceiverFunc)(*mData);
}

}




