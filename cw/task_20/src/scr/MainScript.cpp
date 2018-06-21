#include "MainScript.h"

#include "common.h"
#include "scr/CarListScript.h"

#include <wce/ui/element/Notification.h>
#include <wce/ui/element/menu/Menu.h>
#include <wce/ui/element/Label.h>
#include <wce/ui/element/menu/MenuSeparator.h>

using namespace wce;

MainScript::MainScript() {
    {
        auto& e = makeElement<Notification>(templates::infoNotification());
        e.text
            .setFore(console::C_LT_GREEN)
            .append("СИСТЕМА УПРАВЛЕНИЯ ДАННЫМИ\n"_dos)
            .setFore(console::C_LT_BLUE)
            .append("ТРАНСПОРТНОГО АГЕНСТВА\n"_dos);
    }

    makeElement<Label>(templates::wrapLabel(2));

    {
        auto& e = makeElement<Menu>(templates::simpleMenu());

        e.makeItem<MenuItem>(ID_MENU_CARS, "1|t")
            .text.append("Управление транспортом"_dos);
        e.makeItem<MenuItem>(ID_MENU_CLIENTS, "2|c")
            .text.append("Управление клиентами"_dos);
        e.makeItem<MenuItem>(ID_MENU_RENT, "3|r")
            .text.append("Управление арендой"_dos);
        e.makeItem<MenuSeparator>(ID_MENU_SEP1);
        e.makeItem<MenuItem>(ID_MENU_EXIT, "0|q")
            .text.append("Выход из программы"_dos);

        auto &d = makeElement<MenuReader>(templates::simpleMenuReader());
        d.addResultReadCallback(onMenuResult);

        e.assignReader(d);
    }
}

MainScript::~MainScript() { }

bool MainScript::onMenuResult(MenuReaderResult &result) {
    if (result.getState() == ReaderResultState::VALUE_READ) {
        switch (result.getValue()) {
            case ID_MENU_CARS: {
                CarListScript().run();
                return true;
            }
            case ID_MENU_EXIT:
                this->abort();
                return true;
            default:
                break;
        }
    }

    std::string errorText = "Ошибка!";
    if (result.getState() == ReaderResultState::CONVERT_FAIL)
        errorText = result.getConvertFail();

    StyledText()
        .setFore(console::C_LT_RED)
        .append(errorText)
        .outputTo(std::cout);
    console::waitAnyKey();

    return false;
}
