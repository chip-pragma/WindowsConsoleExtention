#pragma once

#include <cpe/ui/BaseView.h>
#include <cpe/ui/element/Label.h>

#include "../vm/CarListVM.h"

class CarListView : public cpe::BaseView<CarListVM> {
    cpe::Label m_lTest;
public:
    ~CarListView() override;

protected:
    void onInitialize() override;
};


