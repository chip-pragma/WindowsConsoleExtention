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
        auto& e = makeElement<Notification>(templates::infoNotification());
        e.text
            .setFore(console::C_LT_GREEN)
            .append("СИСТЕМА УПРАВЛЕНИЯ ДАННЫМИ\n"_dos)
            .setFore(console::C_LT_YELLOW)
            .append("ТРАНСПОРТНОГО АГЕНСТВА\n"_dos);
    }

    makeElement<Label>(tempLabelWraps);

    {
        auto& e = makeElement<Menu>();
        e.commandColor.foreground = console::C_LT_GREEN;
        e.caption.append("Главное меню"_dos);
        auto &eb = e.border;
        eb.style.apply(BorderStyle::DB_OUT_H);
        eb.color.foreground = console::C_LT_TEAL;
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
        d.color = {console::C_LT_TEAL, console::C_DK_BLUE};
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
        .setFore(wce::console::C_LT_RED)
        .append("Неверная комадна меню\n"_dos)
        .outputTo(std::cout);
    wce::console::waitAnyKey();
    return false;
}
