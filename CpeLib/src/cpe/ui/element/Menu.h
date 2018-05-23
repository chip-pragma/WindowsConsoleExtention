#pragma once

#include <string>
#include <unordered_map>

#include "cpe/ui/BaseWriterData.h"
#include "cpe/ui/BaseWriter.h"

namespace cpe {

class MenuData : public BaseWriterData {
public:

    ~MenuData() override;

    void add_item(uint32_t itemId, const std::string &text);

    void remove_item(uint32_t itemId);

protected:
    std::unordered_map<uint32_t, std::string> mItems;
};

class Menu : public BaseWriter<MenuData> {
public:
    ~Menu() override;

protected:
    void on_write(Buffer &buf) override;
};

}




