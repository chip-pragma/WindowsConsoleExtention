#include "CarListView.h"

#include "../common.h"
#include "../model/Car.h"

CarListView::CarListView()
    : BaseView(),
      m_mControl_miAdd("1|a"),
      m_mControl_miEdit("2|e"),
      m_mControl_miRemove("3|r"),
      m_mControl_miGoToPage("4|g"),
      m_mControl_miBack("0|b") {

}

CarListView::~CarListView() { }

void CarListView::onInitialize() {
    using namespace cpe;

    {
        const TextColor HEADER_COLOR(Colors::WHITE, Colors::BLUE);
        const TextColor BORDER_COLOR(Colors::TEAL, std::nullopt);

        m_dtCars.bindData(&CarListVM::onDataTableInit);
        auto &d = m_dtCars.getData();
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
        m_dtCars_dtcSeats.setSortFunctor(
            [](const Car &c1, const Car &c2) -> bool {
                return (c1.getSeats() < c2.getSeats());
            });

        m_dtCars_dtcStateNumber.getHeader()
            .setColor(HEADER_COLOR)
            .append("ГОСНОМЕР"_dos);

        m_dtCars.makeColumn(Car::CF_MARK, 0);
        m_dtCars.makeColumn(Car::CF_MAKER, 0);
        m_dtCars.makeColumn(Car::CF_SEATS, 0);
        m_dtCars.makeColumn(Car::CF_STATE_NUMBER, 0);
    }

    {
        // FIXME ошибка при уничтожении Label (возможно двойное удаление LabelData) (Проверить на новой SM)
        m_lPageOf.bindData(&CarListVM::onLabelPageInit);
        m_lPageOf.getData().setCallPause(true);
    }

    append(m_dtCars);
    append(m_lPageOf);
}
