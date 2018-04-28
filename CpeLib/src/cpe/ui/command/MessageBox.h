#pragma once

#include <string>

#include "cpe/ui/Buffer.h"
#include "cpe/core/Color.h"
#include "ACommand.h"
#include "cpe/utils/property/AProperties.h"
#include "cpe/utils/property/PropertyRW.h"
#include "cpe/ui/style/DualBorder.h"
#include "Menu.h"

#undef MessageBox

namespace cpe {

class MessageBox : public ACommand, public AProperties {
public:
    MessageBox();

    ~MessageBox() override;

    struct {
        PropertyRW<Color> fore;
        PropertyRW<Color> back;
        PropertyRW<std::string> text;
        PropertyRW<char> icon;
    } caption;

    struct {
        PropertyRW<Color> fore;
        PropertyRW<Color> back;
        PropertyRW<std::string> text;
//        PropertyRW<Menu> menu;
    } message;

    struct {
        PropertyRW<Color> *fore;
        PropertyRW<Color> *back;
        PropertyRW<DualBorder> *dual;
    } border;

    void *run(Buffer &buf, std::vector<AReader *> &readers) override;
};

}




