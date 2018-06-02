#include "CarListView.h"

#include "TransAgency/common.h"

CarListView::~CarListView() {

}

void CarListView::onInitialize() {
    {
        auto &d =  m_lTest.getData();
        d.setCallPause(true);
        d.getText()
            .setFore(cpe::Colors::GREEN)
            .append("Проверка, епта!"_dos);
    }

    addElement(m_lTest);
}
