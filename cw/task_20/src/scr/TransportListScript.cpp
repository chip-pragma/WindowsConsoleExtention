#include "TransportListScript.h"

#include <sstream>

#include <wce/ui/style/TextColor.h>
#include <wce/ui/element/menu/Menu.h>
#include <wce/ui/element/menu/MenuItem.h>

#include "common.h"
#include "TransAgency.h"

using namespace wce;

TransportListScript::TransportListScript() {
    TextColor tempHeaderColor(console::C_WHITE, console::C_DK_BLUE);
    TextColor tempBorderColor(console::C_DK_TEAL, std::nullopt);

    {
        auto &e = makeElement<Notification>();
        e.text = StyledText().append("Управление транспортом"_dos);
    }

    {
        using Column = DataTableColumn<Transport>;

        auto &e = makeElement<DataTable<Transport>>();
        m_dtCars = &e;
        e.addBeforeRunCallback(onBeforeRunDataTableCar);
        e.border.color = tempBorderColor;

        e.makeColumn<Column>(Transport::ID_FIELD_MARK)
            .header
            .setColor(tempHeaderColor).append("МАРКА"_dos);
        e.makeColumn<Column>(Transport::ID_FIELD_MAKER)
            .header
            .setColor(tempHeaderColor).append("ПРОИЗВОДИТЕЛЬ"_dos);
        e.makeColumn<Column>(Transport::ID_FIELD_SEATS)
            .header
            .setColor(tempHeaderColor).append("СИДЕНИЙ"_dos);
        e.makeColumn<Column>(Transport::ID_FIELD_STATE_NUMBER)
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

        e.makeItem<MenuItem>(ID_MENU_ADD, "1|add")
            .text.append("Добавить"_dos);
        e.makeItem<MenuItem>(ID_MENU_EDIT, "1|edit")
            .text.append("Изменить"_dos);
        e.makeItem<MenuItem>(ID_MENU_EXIT, "0|back")
            .text.append("В главное меню"_dos);

        auto &d = makeElement<MenuReader>(templates::simpleMenuReader());
        d.addResultReadCallback(onMenuResult);

        e.assignReader(d);
    }
}

TransportListScript::~TransportListScript() { }

void TransportListScript::onBeforeRunDataTableCar(DataTable<Transport> &element) {
    element.setDataSource(TransAgency::get().getCarList());
    element.sortBy = Transport::ID_FIELD_MARK;
}

void TransportListScript::onBeforeRunLabelPageInfo(Label &element) {
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

bool TransportListScript::onMenuResult(wce::MenuReaderResult &result) {
    return true;
}
