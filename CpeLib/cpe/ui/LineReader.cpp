#include "LineReader.h"


namespace cpe::ui {

std::string LineReader::read() const {
    std::string str;
    std::getline(std::cin, str);
    fireBinded(str);
    return str;
}

void LineReader::run() {
    read();
}

}



