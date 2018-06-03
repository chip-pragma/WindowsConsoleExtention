#include "CarListView.h"

#include "../common.h"
#include "../model/Car.h"

CarListView::~CarListView() { }

void CarListView::onInitialize() {
    {
        m_dtCars.bindData(&CarListVM::onDataTableInit);
        auto &d = m_dtCars.getData();
        d.setCallPause(true);

        m_dtCars_dtcMark.getHeader()
            .setColor({cpe::Colors::BLACK, cpe::Colors::LT_GREEN})
            .append("МАРКА"_dos);
        m_dtCars_dtcMark.getCellTextColor().getFore() = cpe::Colors::LT_GREEN;

        m_dtCars_dtcMaker.getHeader()
            .setColor({cpe::Colors::BLACK, cpe::Colors::LT_RED})
            .append("ПРОИЗВОДИТЕЛЬ"_dos);
        m_dtCars_dtcMaker.getCellTextColor().getFore() = cpe::Colors::LT_RED;

        m_dtCars_dtcSeats.getHeader()
            .setColor({cpe::Colors::BLACK, cpe::Colors::LT_TEAL})
            .append("СИДЕНИЙ"_dos);
        m_dtCars_dtcSeats.getCellTextColor().getFore() = cpe::Colors::LT_TEAL;

        m_dtCars_dtcStateNumber.getHeader()
            .setColor({cpe::Colors::BLACK, cpe::Colors::LT_PURPLE})
            .append("ГОСНОМЕР"_dos);
        m_dtCars_dtcStateNumber.getCellTextColor().getFore() = cpe::Colors::LT_PURPLE;

        m_dtCars.addColumn(Car::F_MARK, m_dtCars_dtcMark);
        m_dtCars.addColumn(Car::F_MAKER, m_dtCars_dtcMaker);
        m_dtCars.addColumn(Car::F_SEATS, m_dtCars_dtcSeats);
        m_dtCars.addColumn(Car::F_STATE_NUMBER, m_dtCars_dtcStateNumber);
    }

    addElement(m_dtCars);
}
