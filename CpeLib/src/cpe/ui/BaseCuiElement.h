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

    virtual const TData &getData() const;

    virtual TData &getData();

    template<class TViewModel>
    void bindData(DataReceiverFunc<TViewModel> func);

    void fireData(IViewModel &ctrl);

protected:
    using _PureDataReceiverFunc = void (IViewModel::*)(TData &);

    void onBeforeRun() override { }

    void onRun() override { }

    void onAfterRun() override { }

    TData *mData;
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
const TData &BaseCuiElement<TData>::getData() const {
    return *mData;
}

template<class TData>
TData &BaseCuiElement<TData>::getData() {
    return *mData;
}

template<class TData>
template<class TViewModel>
void BaseCuiElement<TData>::bindData(DataReceiverFunc<TViewModel> func) {
    mDataReceiverFunc = static_cast<_PureDataReceiverFunc>(func);
}

template<class TData>
void BaseCuiElement<TData>::fireData(IViewModel &ctrl) {
    if (mDataReceiverFunc)
        (ctrl.*mDataReceiverFunc)(*mData);
}

}




