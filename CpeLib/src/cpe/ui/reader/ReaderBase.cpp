#include <cpe/ui/style/TextColor.h>
#include "ReaderBase.h"

namespace cpe {

ReaderInitializer::ReaderInitializer(ReaderBase &element)
        : IInitializer(static_cast<ICuiElement &>(element)),
          mReader(element) {

}

TextColor &ReaderInitializer::read_color() {
    return mReader.read_color();
}

void ReaderInitializer::add_command(const std::string &command) {
    mReader.add_command(command);
}

void ReaderInitializer::remove_command(const std::string &command) {
    mReader.remove_command(command);
}

const TextColor &ReaderBase::read_color() const {
    return mReadStyle;
}

TextColor &ReaderBase::read_color() {
    return mReadStyle;
}

void ReaderBase::add_command(const std::string &command) {
    mCommands.insert(command);
}

void ReaderBase::remove_command(const std::string &command) {
    mCommands.erase(command);
}

}



