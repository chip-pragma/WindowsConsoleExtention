#pragma once

#include <cstdint>

#include <cpe/ui/BaseViewModel.h>
#include <cpe/ui/element/menu/MenuReader.h>
#include <cpe/ui/element/Label.h>

class MainVM : public cpe::BaseViewModel {
public:
    enum MainMenuIds : uint32_t {
        ID_MM_EXIT = 0,
        ID_MM_CARS,
        ID_MM_CLIENTS,
        ID_MM_RENT,
        ID_MM_SEP1,
        ID_MM_SEP2,
    };

    bool onMainMenuReaderResult(cpe::MenuReaderResult &result);

    void onLabelTestInit(cpe::LabelData &data);
};


