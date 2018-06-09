#include "MainView.h"
#include "TransAgency/common.h"

#include <cpe/tool/Encoder.h>

MainView::MainView()
    : BaseView(),
      m_mMain_miCars("1|t"),
      m_mMain_miClients("2|c"),
      m_mMain_miRent("3|r"),
      m_mMain_miExit("0|q") { }

MainView::~MainView() { }

void MainView::onInitialize() {
    using namespace cpe;

    m_lWraps.getData().getText().append("\n\n");

    {
        auto &d = m_nCaption.getData();
        d.getBorder().getStyle().apply(BorderStyle::DB_ALL);
        d.getText()
            .setFore(Colors::LT_GREEN)
            .append("СИСТЕМА УПРАВЛЕНИЯ ДАННЫМИ\n"_dos)
            .setFore(Colors::LT_YELLOW)
            .append("ТРАНСПОРТНОГО АГЕНСТВА\n"_dos);
        d.getIcon() = StyledChar('i', {Colors::LT_TEAL, std::nullopt});
    }

    {
        m_mMain.assignReader(m_mrMain);
        auto &d = m_mMain.getData();
        d.getCommandColor().getFore() = Colors::LT_PURPLE;
        d.getCaption().append("Главное меню"_dos);
        auto &db = d.getBorder();
        db.getStyle().apply(BorderStyle::DB_OUT_H);
        db.getColor().getFore() = Colors::LT_TEAL;
        d.getReaderHint().append("Выберите действие"_dos);
    }

    {
        m_mrMain.bindResult(&MainVM::onMainMenuReaderResult);
        auto &d = m_mrMain.getData();
        d.getColorRead() = {Colors::LT_TEAL, Colors::BLUE};
        d.getErrorText() = "Неверный пункт меню"_dos;
    }

    {
        m_mMain_miCars.getText()
            .setFore(Colors::WHITE)
            .append("Управление транспортом"_dos);

        m_mMain_miClients.getText()
            .setFore(Colors::WHITE)
            .append("Управление клиентами"_dos);

        m_mMain_miRent.getText()
            .setFore(Colors::WHITE)
            .append("Управление арендой"_dos);

        m_mMain_miExit.getText()
            .setFore(Colors::WHITE)
            .append("Выход из программы"_dos);

        m_mMain.addItem(MainVM::ID_MM_CARS, m_mMain_miCars);
        m_mMain.addItem(MainVM::ID_MM_CLIENTS, m_mMain_miClients);
        m_mMain.addItem(MainVM::ID_MM_RENT, m_mMain_miRent);
        m_mMain.addItem(MainVM::ID_MM_SEP1, m_mMain_ms1);
        m_mMain.addItem(MainVM::ID_MM_EXIT, m_mMain_miExit);
    }

    {
        m_lTest.bindData(&MainVM::onLabelTestInit);
    }

    addElement(m_nCaption);
    addElement(m_lWraps);
    addElement(m_mMain);
    addElement(m_lTest);
    addElement(m_mrMain);
}

