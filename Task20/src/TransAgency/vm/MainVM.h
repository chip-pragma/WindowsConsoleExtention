#pragma once

#include <cstdint>

#include <cpe/ui/IViewModel.h>
#include <cpe/ui/ReaderResult.h>

class MainVM : public cpe::IViewModel {
public:
    enum MainMenuIds : uint32_t {
        ID_MM_EXIT = 0,
        ID_MM_CARS,
        ID_MM_CLIENTS,
        ID_MM_RENT,
        ID_MM_SEP1,
        ID_MM_SEP2,
    };

    bool onMainMenuResult(cpe::ReaderResult<uint32_t> &result);
};


