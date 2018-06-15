#pragma once

#include <wce/ui/BaseScript.h>
#include <wce/ui/element/menu/MenuReader.h>

class MainScript : public wce::BaseScript {
public:
    enum : uint32_t {
        ID_MM_EXIT = 0,
        ID_MM_CARS,
        ID_MM_CLIENTS,
        ID_MM_RENT,
        ID_MM_SEP1,
        ID_MM_SEP2,
    };

    MainScript();

    ~MainScript() override;

protected:
    bool onMenuResult(wce::MenuReaderResult& result);
};


