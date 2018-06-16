#include "CarListScript.h"

#include <sstream>

#include <wce/ui/style/TextColor.h>

#include "common.h"
#include "TransAgency.h"

CarListScript::CarListScript() {
    using namespace wce;

    TextColor tempHeaderColor(console::cWhite, console::cBlue);
    TextColor tempBorderColor(console::cTeal, std::nullopt);

    {
        using Column = DataTableColumn<Car>;

        auto &e = makeElement<DataTable<Car>>();
        m_dtCars = &e;
        e.addBeforeRunCallback(onBeforeRunDataTableCar);
        e.border.color = tempBorderColor;

        e.makeColumn<Column>(Car::ID_FIELD_MARK)
            .header
            .setColor(tempHeaderColor).append("МАРКА"_dos);

        e.makeColumn<Column>(Car::ID_FIELD_MAKER)
            .header
            .setColor(tempHeaderColor).append("ПРОИЗВОДИТЕЛЬ"_dos);

        e.makeColumn<Column>(Car::ID_FIELD_SEATS)
            .header
            .setColor(tempHeaderColor).append("СИДЕНИЙ"_dos);

        {
            auto &ec = e.makeColumn<Column>(Car::ID_FIELD_STATE_NUMBER);
            ec.header
                .setColor(tempHeaderColor).append("ГОСНОМЕР"_dos);
            ec.sortPredicate =
                [](const Car &c1, const Car &c2) -> bool {
                    return (c1.getSeats() < c2.getSeats());
                };
        }
    }

    {
        auto &e = makeElement<Label>();
        e.addBeforeRunCallback(onBeforeRunLabelPageInfo);
        e.waitAnyKey = true;
    }
}

CarListScript::~CarListScript() { }

void CarListScript::onBeforeRunDataTableCar(wce::DataTable<Car> &element) {
    element.setDataSource(TransAgency::get().getCarList());
    element.sortBy = Car::ID_FIELD_MARK;
}

void CarListScript::onBeforeRunLabelPageInfo(wce::Label &element) {
    std::stringstream ss;
    ss << "[Страница "
       << m_dtCars->pageNumber + 1
       << " из "
       << m_dtCars->getPageCount()
       << "]\n";
    element.text
        .clear().append(fromUtf8ToDos866(ss.str()));
    this->abort();
}
