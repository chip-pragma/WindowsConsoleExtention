#include "MainView.h"
#include "TransAgency/common.h"

#include <cpe/tool/Encoder.h>

MainView::MainView()
    : BaseView(),
      m_mMain_nmiCars("1|car"),
      m_mMain_nmiClients("2|client"),
      m_mMain_nmiRent("3|rent"),
      m_mMain_nmiExit("0|exit") { }

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
        m_mMain.assignReader(m_mrMain);
        auto &d = m_mMain.data();
        d.getCommandColor().foreground() = Colors::LT_PURPLE;
        d.width() = 20;
        d.getCaption()
            .color({Colors::LT_TEAL, std::nullopt})
            .append("Главное меню"_dos);
        d.getBorder().style().apply(BorderStyle::DB_OUT_H);
        d.getReaderHint()
            .color({Colors::LT_TEAL, std::nullopt})
            .append("Напишите эссе, какой бы вы выбрали сраный пункт меню."_dos);
    }

    {
        m_mrMain.bind_result(&MainVM::main_menu_result);
        auto &d = m_mrMain.data();
        d.read_color() = {Colors::LT_TEAL, Colors::BLUE};
        d.convert_fail_text() = "Неверный пункт меню"_dos;
    }

    {
        m_mMain_nmiCars.getText()
            .color({Colors::WHITE, std::nullopt})
            .append("Транспорт"_dos);
        m_mMain.addItem(MainVM::ID_MM_CARS, m_mMain_nmiCars);

        m_mMain_nmiClients.getText()
            .color({Colors::WHITE, std::nullopt})
            .append("Клиенты"_dos);
        m_mMain.addItem(MainVM::ID_MM_CLIENTS, m_mMain_nmiClients);

        m_mMain_nmiRent.getText()
            .color({Colors::WHITE, std::nullopt})
            .append("Аренда"_dos);
        m_mMain.addItem(MainVM::ID_MM_RENT, m_mMain_nmiRent);

        m_mMain_nmiExit.getText()
            .color({Colors::WHITE, std::nullopt})
            .append("Выход"_dos);
        m_mMain.addItem(MainVM::ID_MM_EXIT, m_mMain_nmiExit);
    }

    push(m_nCaption);
    push(m_lWraps);
    push(m_mMain);
    push(m_mrMain);
}

