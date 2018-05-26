#include "MainView.h"
#include "TransAgency/common.h"

#include <cpe/tool/Encoder.h>

MainView::MainView() : BaseView() { }

MainView::~MainView() { }


void MainView::on_initialize() {
    m_lWraps.data().text().append("\n\n");

    auto &ncData = m_nCaption.data();
    ncData.border().style().apply(cpe::BorderStyle::DB_ALL);
    ncData.text()
        .color({cpe::Colors::LT_GREEN, std::nullopt})
        .append("СИСТЕМА УПРАВЛЕНИЯ ДАННЫМИ\n"_dos)
        .color({cpe::Colors::LT_YELLOW, std::nullopt})
        .append("ТРАНСПОРТНОГО АГЕНСТВА\n"_dos);
    ncData.icon() = cpe::StyledChar('i', {cpe::Colors::LT_TEAL, std::nullopt});
    ncData.wait(true);

    {
        auto &d = m_mMain.data();
        d.command_color().foreground() = cpe::Colors::LT_RED;
        d.width() = 30;
        d.caption()
            .color({std::nullopt, cpe::Colors::WHITE})
            .append("Заголовок "_dos)
            .color({std::nullopt, cpe::Colors::LT_TEAL})
            .append(" этой "_dos)
            .color({std::nullopt, cpe::Colors::LT_RED})
            .append(" менюшки"_dos);
        auto &db = d.border();
        db.color().foreground() = cpe::Colors::LT_TEAL;
        auto &dbs = db.style();
        dbs.apply(cpe::BorderStyle::DB_OUT_H);
        dbs.final_encoding() = cpe::Encoder(cpe::Encoder::CP866);
    }

    m_mMain_nmiCars.index() = MainVM::ID_MM_CARS;
    m_mMain_nmiCars.text().append("Транспорт"_dos);
    m_mMain.add_item(MainVM::ID_MM_CARS, m_mMain_nmiCars);

    m_mMain_nmiClients.index() = MainVM::ID_MM_CLIENTS;
    m_mMain_nmiClients.text().append("Клиенты"_dos);
    m_mMain.add_item(MainVM::ID_MM_CLIENTS, m_mMain_nmiClients);

    m_mMain_nmiRent.index() = MainVM::ID_MM_RENT;
    m_mMain_nmiRent.text().append("Аренда"_dos);
    m_mMain.add_item(MainVM::ID_MM_RENT, m_mMain_nmiRent);

    m_mMain_nmiExit.index() = MainVM::ID_MM_EXIT;
    m_mMain_nmiExit.text().append("Выход"_dos);
    m_mMain.add_item(MainVM::ID_MM_EXIT, m_mMain_nmiExit);

    push(m_nCaption);
    push(m_lWraps);
    push(m_mMain);
}

