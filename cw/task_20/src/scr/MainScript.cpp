#include "MainScript.h"

#include "common.h"
#include "scr/CarListScript.h"

#include <wce/ui/element/Notification.h>
#include <wce/ui/element/menu/Menu.h>
#include <wce/ui/element/Label.h>
#include <wce/ui/element/menu/MenuSeparator.h>

using namespace wce;

MainScript::MainScript() {
    Label tempLabelWraps;
    tempLabelWraps.text.append("\n\n");

    {
        auto& e = makeElement<Notification>();
        e.border.style.apply(BorderStyle::DB_ALL);
        e.text
            .setFore(console::cGreenLt)
            .append("СИСТЕМА УПРАВЛЕНИЯ ДАННЫМИ\n"_dos)
            .setFore(console::cYellowLt)
            .append("ТРАНСПОРТНОГО АГЕНСТВА\n"_dos);
        e.icon = StyledChar('i', {console::cTealLt, std::nullopt});
    }

    makeElement<Label>(tempLabelWraps);

    {
        auto& e = makeElement<Menu>();
        e.commandColor.foreground = console::cGreenLt;
        e.caption.append("Главное меню"_dos);
        auto &eb = e.border;
        eb.style.apply(BorderStyle::DB_OUT_H);
        eb.color.foreground = console::cTealLt;
        e.readerHint.append("Выберите действие"_dos);

        e.makeItem<MenuItem>(ID_MM_CARS, "1|t")
            .text.append("Управление транспортом"_dos);
        e.makeItem<MenuItem>(ID_MM_CLIENTS, "2|c")
            .text.append("Управление клиентами"_dos);
        e.makeItem<MenuItem>(ID_MM_RENT, "3|r")
            .text.append("Управление арендой"_dos);
        e.makeItem<MenuSeparator>(ID_MM_SEP1);
        e.makeItem<MenuItem>(ID_MM_EXIT, "0|q")
            .text.append("Выход из программы"_dos);

        auto &d = makeElement<MenuReader>();
        d.addResultReadCallback(onMenuResult);
        d.color = {console::cTealLt, console::cBlue};
        d.errorText = "Неверный пункт меню"_dos;

        e.assignReader(d);
    }
}

MainScript::~MainScript() { }

bool MainScript::onMenuResult(wce::MenuReaderResult &result) {
    if (result.getType() == wce::ReaderResultType::VALUE) {
        switch (result.getValue()) {
            case ID_MM_CARS: {
                CarListScript().run();
                return true;
            }
            case ID_MM_EXIT:
                this->abort();
                return true;
            default:
                break;
        }
    }

    wce::StyledText()
        .setFore(wce::console::cRedLt)
        .append("Неверная комадна меню\n"_dos)
        .outputTo(std::cout);
    wce::console::waitAnyKey();
    return false;
}
