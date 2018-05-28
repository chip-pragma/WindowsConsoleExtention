#include "MainView.h"
#include "TransAgency/common.h"

#include <cpe/tool/Encoder.h>

MainView::MainView() : BaseView() { }

MainView::~MainView() { }


void MainView::on_initialize() {
    using namespace cpe;

    m_lWraps.data().text().append("\n\n");

    {
        auto &d = m_nCaption.data();
        d.border().style().apply(BorderStyle::DB_ALL);
        d.text()
            .color({Colors::LT_GREEN, std::nullopt})
            .append("СИСТЕМА УПРАВЛЕНИЯ ДАННЫМИ\n"_dos)
            .color({Colors::LT_YELLOW, Colors::BLUE})
            .append("ТРАНСПОРТНОГО АГЕНСТВА\n"_dos);
        d.icon() = StyledChar('i', {Colors::LT_TEAL, std::nullopt});
        d.wait(true);
    }

    {
        m_mMain.assign_reader(m_mrMain);
        auto &d = m_mMain.data();
        d.command_color().foreground() = Colors::LT_PURPLE;
        d.width() = 80;
        d.caption()
            .color({Colors::LT_TEAL, std::nullopt})
            .append("Главное меню"_dos);
        d.border().style().apply(BorderStyle::DB_OUT_H);
    }

    {
        m_mrMain.bind_result(&MainVM::main_menu_result);
        auto& d = m_mrMain.data();
        d.read_color() = {Colors::LT_TEAL, Colors::BLUE};
        d.convert_fail_text() = "Неверный пункт меню"_dos;
    }

    {
        m_mMain_nmiCars.index() = MainVM::ID_MM_CARS;
        m_mMain_nmiCars.text()
            .color({Colors::WHITE, std::nullopt})
            .append("Транспорт"_dos);
        m_mMain.add_item(MainVM::ID_MM_CARS, m_mMain_nmiCars);

        m_mMain_nmiClients.index() = MainVM::ID_MM_CLIENTS;
        m_mMain_nmiClients.text()
            .color({Colors::WHITE, std::nullopt})
            .append("Клиенты"_dos);
        m_mMain.add_item(MainVM::ID_MM_CLIENTS, m_mMain_nmiClients);

        m_mMain_nmiRent.index() = MainVM::ID_MM_RENT;
        m_mMain_nmiRent.text()
            .color({Colors::WHITE, std::nullopt})
            .append("Аренда"_dos);
        m_mMain.add_item(MainVM::ID_MM_RENT, m_mMain_nmiRent);

        m_mMain_nmiExit.index() = MainVM::ID_MM_EXIT;
        m_mMain_nmiExit.text()
            .color({Colors::WHITE, std::nullopt})
            .append("Выход"_dos);
        m_mMain.add_item(MainVM::ID_MM_EXIT, m_mMain_nmiExit);
    }

    push(m_nCaption);
    push(m_lWraps);
    push(m_mMain);
    push(m_mrMain);
}

