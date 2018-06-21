#include "CarListScript.h"

#include <sstream>

#include <wce/ui/style/TextColor.h>

#include "common.h"
#include "TransAgency.h"

using namespace wce;

CarListScript::CarListScript() {
    TextColor tempHeaderColor(console::C_WHITE, console::C_DK_BLUE);
    TextColor tempBorderColor(console::C_DK_TEAL, std::nullopt);

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
        e.makeColumn<Column>(Car::ID_FIELD_STATE_NUMBER)
            .header
            .setColor(tempHeaderColor).append("ГОСНОМЕР"_dos);
    }

    {
        auto &e = makeElement<Label>();
        e.addBeforeRunCallback(onBeforeRunLabelPageInfo);
        e.waitAnyKey = true;
    }

    {
        auto &e = makeElement<Menu>(templates::simpleMenu());

        e.makeItem()
    }
}

CarListScript::~CarListScript() { }

void CarListScript::onBeforeRunDataTableCar(DataTable<Car> &element) {
    element.setDataSource(TransAgency::get().getCarList());
    element.sortBy = Car::ID_FIELD_MARK;
}

void CarListScript::onBeforeRunLabelPageInfo(Label &element) {
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
