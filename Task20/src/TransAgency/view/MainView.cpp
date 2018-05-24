#include "MainView.h"
#include "TransAgency/common.h"

#include <cpe/tool/Encoder.h>

MainView::MainView() : BaseView() { }

MainView::~MainView() { }


void MainView::on_initialize() {
    m_lWraps.data().text().push_back("\n\n");

    auto &ncData = m_nCaption.data();
    ncData.border().style().apply(cpe::BorderStyle::DB_ALL);
    ncData.text().push_back({"СИСТЕМА УПРАВЛЕНИЯ ДАННЫМИ\n"_dos, {cpe::Colors::LT_GREEN, std::nullopt}});
    ncData.text().push_back({"ТРАНСПОРТНОГО АГЕНСТВА"_dos, {cpe::Colors::LT_YELLOW, cpe::Colors::BLUE}});
    ncData.icon() = cpe::StyledChar('i', {cpe::Colors::LT_TEAL, std::nullopt});
    ncData.wait(true);

    // TODO сократитьт монструозное инициализирование (использовать Named Parameter Idiom)

    m_mMain.data().command_color().foreground() = cpe::Colors::LT_RED;
    m_mMain.data().border().style().apply(cpe::BorderStyle::DB_OUT_H);
    m_mMain.data().border().style().final_encoding() = cpe::Encoder(cpe::Encoder::CP866);
    m_mMain.data().border().color().foreground() = cpe::Colors::LT_TEAL;
    m_mMain.data().width() = 30;
    m_mMain.data().caption().push_back({"Заголовок "_dos, {cpe::Colors::BLACK, cpe::Colors::WHITE}});
    m_mMain.data().caption().push_back({" этой "_dos, {cpe::Colors::BLACK, cpe::Colors::LT_TEAL}});
    m_mMain.data().caption().push_back({" менюшки"_dos, {cpe::Colors::BLACK, cpe::Colors::LT_RED}});

    m_mMain_nmiCars.index() = MainVM::ID_MM_CARS;
    m_mMain_nmiCars.text() = {"Транспорт"_dos};
    m_mMain.add_item(MainVM::ID_MM_CARS, m_mMain_nmiCars);

    m_mMain_nmiClients.index() = MainVM::ID_MM_CLIENTS;
    m_mMain_nmiClients.text() = {"Клиенты"_dos};
    m_mMain.add_item(MainVM::ID_MM_CLIENTS, m_mMain_nmiClients);

    m_mMain_nmiRent.index() = MainVM::ID_MM_RENT;
    m_mMain_nmiRent.text() = {"Аренда"_dos};
    m_mMain.add_item(MainVM::ID_MM_RENT, m_mMain_nmiRent);

    m_mMain_nmiExit.index() = MainVM::ID_MM_EXIT;
    m_mMain_nmiExit.text() = {"Выход"_dos};
    m_mMain.add_item(MainVM::ID_MM_EXIT, m_mMain_nmiExit);

    push(m_nCaption);
    push(m_lWraps);
    push(m_mMain);
}

