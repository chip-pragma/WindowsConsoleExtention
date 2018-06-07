#include "CarListView.h"

#include "../common.h"
#include "../model/Car.h"

CarListView::~CarListView() { }

void CarListView::onInitialize() {
    using namespace cpe;
    
    {
        const TextColor HEADER_COLOR(Colors::WHITE, Colors::BLUE);
        const TextColor BORDER_COLOR(Colors::TEAL, std::nullopt);

        m_dtCars.bindData(&CarListVM::onDataTableInit);
        auto &d = m_dtCars.getData();
        d.setCallPause(true);
        d.getBorder().getColor() = BORDER_COLOR;

        m_dtCars_dtcMark.getHeader()
            .setColor(HEADER_COLOR)
            .append("МАРКА"_dos);

        m_dtCars_dtcMaker.getHeader()
            .setColor(HEADER_COLOR)
            .append("ПРОИЗВОДИТЕЛЬ"_dos);

        m_dtCars_dtcSeats.getHeader()
            .setColor(HEADER_COLOR)
            .append("СИДЕНИЙ"_dos);

        m_dtCars_dtcStateNumber.getHeader()
            .setColor(HEADER_COLOR)
            .append("ГОСНОМЕР"_dos);

        m_dtCars.addColumn(Car::CF_MARK, m_dtCars_dtcMark);
        m_dtCars.addColumn(Car::CF_MAKER, m_dtCars_dtcMaker);
        m_dtCars.addColumn(Car::CF_SEATS, m_dtCars_dtcSeats);
        m_dtCars.addColumn(Car::CF_STATE_NUMBER, m_dtCars_dtcStateNumber);
    }

    {
        // TODO текст "страница: Х из Y", затем меню "управление"
    }

    addElement(m_dtCars);
}
