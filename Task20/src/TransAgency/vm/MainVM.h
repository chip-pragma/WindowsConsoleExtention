#pragma once

#include <cstdint>

#include <cpe/ui/IViewModel.h>

class MainVM : public cpe::IViewModel {
public:
    enum MainMenuIds : uint32_t {
        ID_MM_EXIT = 0,
        ID_MM_CARS,
        ID_MM_CLIENTS,
        ID_MM_RENT
    };
};


