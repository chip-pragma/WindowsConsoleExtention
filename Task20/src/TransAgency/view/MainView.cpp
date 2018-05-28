#include "MainView.h"
#include "TransAgency/common.h"

#include <cpe/tool/Encoder.h>

MainView::MainView()
    : BaseView(),
      m_mMain_miCars("1|car"),
      m_mMain_miClients("2|client"),
      m_mMain_miRent("3|rent"),
      m_mMain_miExit("0|exit") { }

MainView::~MainView() { }

void MainView::on_initialize() {
    using namespace cpe;

    m_lWraps.data().text().append("\n\n");

    {
        auto &d = m_nCaption.data();
        d.border().getStyle().apply(BorderStyle::DB_ALL);
        d.text()
            .setColor({Colors::LT_GREEN, std::nullopt})
            .append("СИСТЕМА УПРАВЛЕНИЯ ДАННЫМИ\n"_dos)
            .setColor({Colors::LT_YELLOW, Colors::BLUE})
            .append("ТРАНСПОРТНОГО АГЕНСТВА\n"_dos);
        d.icon() = StyledChar('i', {Colors::LT_TEAL, std::nullopt});
        d.wait(true);
    }

    {
        m_mMain.assignReader(m_mrMain);
        auto &d = m_mMain.data();
        d.getCommandColor().foreground() = Colors::LT_PURPLE;
        d.width() = 70;
        d.getCaption()
            .setColor({Colors::LT_TEAL, std::nullopt})
            .append("Главное меню"_dos);
        d.getBorder().getStyle().apply(BorderStyle::DB_OUT_H);
        d.getReaderHint()
            .setColor({Colors::LT_TEAL, std::nullopt})
            .append("Напишите эссе, какой бы вы выбрали сраный пункт меню."_dos);
    }

    {
        m_mrMain.bind_result(&MainVM::main_menu_result);
        auto &d = m_mrMain.data();
        d.read_color() = {Colors::LT_TEAL, Colors::BLUE};
        d.convert_fail_text() = "Неверный пункт меню"_dos;
    }

    {
        m_mMain_ms1.getText()
            .setColor({Colors::PURPLE, Colors::WHITE})
            .append("сепараторик, епта. Нужно чтобы он быль бооольшим и толстым, сцуко."_dos);

        m_mMain_miCars.getText()
            .setColor({Colors::WHITE, std::nullopt})
            .append("Транспорт"_dos);
        m_mMain.addItem(MainVM::ID_MM_CARS, m_mMain_miCars);

        m_mMain_miClients.getText()
            .setColor({Colors::WHITE, std::nullopt})
            .append("Клиенты"_dos);
        m_mMain.addItem(MainVM::ID_MM_CLIENTS, m_mMain_miClients);

        m_mMain.addItem(MainVM::ID_MM_SEP1, m_mMain_ms1);

        m_mMain_miRent.getText()
            .setColor({Colors::WHITE, std::nullopt})
            .append("Аренда"_dos);
        m_mMain.addItem(MainVM::ID_MM_RENT, m_mMain_miRent);

        m_mMain.addItem(MainVM::ID_MM_SEP1, m_mMain_ms1);

        m_mMain_miExit.getText()
            .setColor({Colors::WHITE, std::nullopt})
            .append("Выход"_dos);
        m_mMain.addItem(MainVM::ID_MM_EXIT, m_mMain_miExit);
    }

    push(m_nCaption);
    push(m_lWraps);
    push(m_mMain);
    push(m_mrMain);
}

