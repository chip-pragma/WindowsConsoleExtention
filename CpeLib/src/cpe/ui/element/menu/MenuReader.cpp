#include "MenuReader.h"

namespace cpe {

MenuReader::~MenuReader() { }

bool MenuReader::on_convert(std::string &srcLine, uint32_t &convertedValue) {
    for (const auto& item : *mItems) {
        if (item.second->get_command() == srcLine) {
            convertedValue = item.first;
            return true;
        }
    }
    return false;
}

}


