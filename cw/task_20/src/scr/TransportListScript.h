#pragma once

#include <wce/ui/BaseScript.h>
#include <wce/ui/element/table/DataTable.h>
#include <wce/ui/element/Label.h>
#include <wce/ui/element/menu/MenuReader.h>

#include "model/Transport.h"

class TransportListScript : public wce::BaseScript {
public:
    enum : uint32_t {
        ID_MENU_EXIT = 0,
        ID_MENU_ADD,
        ID_MENU_EDIT,
        ID_MENU_REMOVE
    };

    TransportListScript();

    ~TransportListScript() override;

protected:
    wce::DataTable<Transport>* m_dtCars;

    void onBeforeRunDataTableCar(wce::DataTable<Transport> &element);

    void onBeforeRunLabelPageInfo(wce::Label &element);

    bool onMenuResult(wce::MenuReaderResult& result);
};


