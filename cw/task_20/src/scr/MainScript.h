#pragma once

#include <wce/ui/BaseScript.h>
#include <wce/ui/element/menu/MenuReader.h>

class MainScript : public wce::BaseScript {
public:
    enum : uint32_t {
        MENU_ID_EXIT = 0,
        MENU_ID_TRANSPORT,
        MENU_ID_CLIENTS,
        MENU_ID_RENT,
        ID_MENU_SEP1, // TODO убрать ID для безкомандных пунктов меню
        ID_MENU_SEP2,
    };

    MainScript();

    ~MainScript() override;

protected:
    bool onMenuResult(wce::MenuReaderResult& result);
};


