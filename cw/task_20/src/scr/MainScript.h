#pragma once

#include <wce/ui/BaseScript.h>
#include <wce/ui/element/menu/MenuReader.h>

class MainScript : public wce::BaseScript {
public:
    enum : uint32_t {
        ID_MENU_EXIT = 0,
        ID_MENU_CARS,
        ID_MENU_CLIENTS,
        ID_MENU_RENT,
        ID_MENU_SEP1,
        ID_MENU_SEP2,
    };

    MainScript();

    ~MainScript() override;

protected:
    bool onMenuResult(wce::MenuReaderResult& result);
};


