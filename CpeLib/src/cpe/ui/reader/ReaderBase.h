#pragma once

#include <string>
#include <set>

#include "IReader.h"
#include "cpe/ui/IInitializer.h"

namespace cpe {

class ReaderBase;

class ReaderInitializer : public IInitializer {
public:
    explicit ReaderInitializer(ReaderBase &element);

    TextColor &read_color();

    void add_command(const std::string &command);

    void remove_command(const std::string &command);

protected:
    ReaderBase &mReader;
};

class ReaderBase : public IReader {
public:
    const TextColor &read_color() const;

    TextColor &read_color();

    void add_command(const std::string &command);

    void remove_command(const std::string &command);

protected:
    TextColor mReadStyle;
    std::set<std::string> mCommands;
};

}




