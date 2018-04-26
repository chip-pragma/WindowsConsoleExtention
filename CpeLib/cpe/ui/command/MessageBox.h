#pragma once

#include <string>

#include "ui/Buffer.h"
#include "core/Color.h"
#include "ui/ACommand.h"
#include "ui/AProperties.h"
#include "ui/style/DualBorder.h"
#include "Menu.h"

#undef MessageBox

namespace cpe {

class MessageBox : public ACommand, public AProperties {
public:
    MessageBox();

    ~MessageBox() override;

    struct {
        Property<Color> *fore;
        Property<Color> *back;
        Property<std::string> *text;
        Property<char> *icon;
    } caption;

    struct {
        Property<Color> *fore;
        Property<Color> *back;
        Property<std::string> *text;
        Property<Menu *> *menu;
    } message;

    struct {
        Property<Color> *fore;
        Property<Color> *back;
        Property<DualBorder> *dual;
    } border;

    void *run(Buffer &buf, std::vector<AReader *> &readers) override;
};

}




