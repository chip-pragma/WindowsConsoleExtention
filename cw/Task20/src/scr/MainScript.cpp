#include "MainScript.h"

#include "common.h"
#include "scr/CarListScript.h"

#include <cpe/ui/element/Notification.h>
#include <cpe/ui/element/menu/Menu.h>
#include <cpe/ui/element/Label.h>
#include <cpe/ui/element/menu/MenuSeparator.h>

using namespace wce;

MainScript::MainScript() {
    Label tempLabelWraps;
    tempLabelWraps.getTextRef().append("\n\n");

    {
        auto& e = makeElement<Notification>();
        e.getBorderRef().getStyleRef().apply(BorderStyle::DB_ALL);
        e.getTextRef()
            .setFore(Colors::LT_GREEN)
            .append("СИСТЕМА УПРАВЛЕНИЯ ДАННЫМИ\n"_dos)
            .setFore(Colors::LT_YELLOW)
            .append("ТРАНСПОРТНОГО АГЕНСТВА\n"_dos);
        e.getIconRef() = StyledChar('i', {Colors::LT_TEAL, std::nullopt});
    }

    makeElement<Label>(tempLabelWraps);

    {
        auto& e = makeElement<Menu>();
        e.getCommandColorRef().getForeRef() = Colors::LT_PURPLE;
        e.getCaptionRef().append("Главное меню"_dos);
        auto &eb = e.getBorderRef();
        eb.getStyleRef().apply(BorderStyle::DB_OUT_H);
        eb.getColorRef().getForeRef() = Colors::LT_TEAL;
        e.getReaderHintRef().append("Выберите действие"_dos);

        e.makeItem<MenuItem>(ID_MM_CARS, "1|t")
            .getTextRef().append("Управление транспортом"_dos);
        e.makeItem<MenuItem>(ID_MM_CLIENTS, "2|c")
            .getTextRef().append("Управление клиентами"_dos);
        e.makeItem<MenuItem>(ID_MM_RENT, "3|r")
            .getTextRef().append("Управление арендой"_dos);
        e.makeItem<MenuSeparator>(ID_MM_SEP1);
        e.makeItem<MenuItem>(ID_MM_EXIT, "0|q")
            .getTextRef().append("Выход из программы"_dos);

        auto &d = makeElement<MenuReader>();
        d.addResultReadCallback(onMenuResult);
        d.getColorReadRef() = {Colors::LT_TEAL, Colors::BLUE};
        d.getErrorTextRef() = "Неверный пункт меню"_dos;

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
        .setFore(wce::Colors::LT_RED)
        .append("Неверная комадна меню\n"_dos)
        .outputTo(std::cout);
    wce::term::callPause();
    return false;
}
